import matplotlib.pyplot as plt
import numpy as np
from skimage.util import img_as_float
from skimage.io import imread
from skimage.io import imsave
from skimage import filter
from skimage.color import rgb2gray
import scipy.ndimage as ndi
from skimage import dtype_limits
from scipy.ndimage import gaussian_filter
from collections import namedtuple

# following import needs OCR libraries
ocr_flag = False
if ocr_flag:
    try:
        import cv2.cv as cv
        import tesseract
    except NameError, ImportError:
        pass

def create_sub_image(img_file, row_begin_frac, row_end_frac, col_begin_frac, col_end_frac):
    img = imread(img_file)
    row_size = img.shape[0]
    col_size = img.shape[1]
    
    row_begin = int(row_begin_frac*row_size)
    row_end = int(row_end_frac*row_size)
    col_begin = int(col_begin_frac*col_size)
    col_end = int(col_end_frac*col_size)
    
    img_array = img[row_begin:row_end, col_begin:col_end]
    return img_array
    
def show_sub_image(img):
    plt.figure()
    plt.imshow(img,cmap=plt.cm.gray)
    plt.axis('off')
    plt.show()
    
def write_sub_image(img,filename):
    #imsave('out.png',img)
    plt.imshow(img)
    plt.savefig(filename)

class text_extraction:
    def __init__(self,img_array):
        if img_array.ndim == 3:
            img_array = rgb2gray(img_array)
        # Convert image to floating point format, with values in [0, 1].
        self.image_float = img_as_float(img_array)
        # output of Otsu's thresholding
        self.binary_image = np.zeros(img_array.shape, bool)
        # stores label no of connected component to which a pixel belongs to
        self.label_matrix = np.zeros(img_array.shape, int)
        
        # stroke width transform matrix
        self.swt_matrix = np.zeros(img_array.shape, int)
        # initialize stroke width of each pixel as inf
        self.swt_matrix += (img_array.shape[0]+img_array.shape[1])
        # Final image which is sent to OCR
        self.text_image = np.zeros(img_array.shape,np.uint8)
        
        # stores information for each of the connected components
        self.label_cc_map = {}
        
        self.point_t = namedtuple('point','row col')
        self.bbox_t = namedtuple('bbox','row_min row_max col_min col_max')
        self.connected_component_t = namedtuple('connected_component','points stroke_width_mean stroke_width_std bounding_box text_possible_flag')

    # main function    
    def process(self):
        self.otsu_thresholding()
        self.connected_component_labeling()
        self.stroke_width_transform()
        self.create_text_image()
        write_sub_image(self.text_image,'out.png')
        
    def otsu_thresholding(self):
        thresh = filter.threshold_otsu(self.image_float)
        self.binary_image = self.image_float > thresh
        
    def connected_component_labeling(self):
        self.create_label_matrix()
        self.create_connected_components()
        
    def create_label_matrix(self):
        # 8-connectivity based
        # two-pass algorithm
        
        label_count = 0;
        equivalent_label_array = [0] # label=0 represents label for non-text pixels i.e. background pixels
        # 1st pass
        for row in range(0,self.binary_image.shape[0]):
            for col in range(0,self.binary_image.shape[1]):
                if self.binary_image[row,col] == False:
                    continue # current pixel is background
                label = 0
                if row > 0:
                    # check north-west, north and north-east neighbours
                    for col_shift in range(-1,2):
                        if ((col + col_shift) < 0) or ((col + col_shift) >= self.binary_image.shape[1]):
                            continue
                        if self.binary_image[row-1,col + col_shift] == True:
                            label_neighbour = self.label_matrix[row-1,col + col_shift]
                            if label > 0:
                                # check for equivalence label
                                if label_neighbour < label:
                                    equivalent_label_array[label] = label_neighbour
                                    label = label_neighbour
                                elif label_neighbour > label:
                                    equivalent_label_array[label_neighbour] = label
                            else:
                                label = label_neighbour
                
                # check the west neighbour
                if col > 0:
                    if self.binary_image[row,col-1] == True:
                        label_neighbour = self.label_matrix[row,col-1]
                        if label > 0:
                            # check for equivalence label
                            if label_neighbour < label:
                                equivalent_label_array[label] = label_neighbour
                                label = label_neighbour
                            elif label_neighbour > label:
                                equivalent_label_array[label_neighbour] = label
                        else:
                            label = label_neighbour
                    
                if label == 0:
                    # none of the above neighbours are foreground
                    label_count += 1
                    label = label_count
                    equivalent_label_array.append(label_count)
                    
                # assign label for current pixel
                self.label_matrix[row,col] = label
                
        # print('label_count: %d\n' % (label_count)) 
        # for equivalence set, assigning smallest label as parent
        for label_i in range(2,len(equivalent_label_array)):
            if equivalent_label_array[label_i] != label_i:
                label = label_i
                # find the smallest label as parent
                while equivalent_label_array[label] != label:
                    label = equivalent_label_array[label]
                # now assign that label as parent to each of these
                label_intermediate = label_i
                while equivalent_label_array[label_intermediate] != label:
                    label_parent = equivalent_label_array[label_intermediate]
                    equivalent_label_array[label_intermediate] = label
                    label_intermediate = label_parent
                    
        # print('equivalent_label_array: %s\n' % (equivalent_label_array))
        equivalent_label_set = list(set(equivalent_label_array))
        # print('label_count(unique): %d\n' % (len(equivalent_label_set)))
                    
        # 2nd pass
        for row in range(0,self.binary_image.shape[0]):
            for col in range(0,self.binary_image.shape[1]):
                if self.binary_image[row,col] == False:
                    continue # current pixel is background
                label = self.label_matrix[row,col]
                if equivalent_label_array[label] != label:
                    self.label_matrix[row,col] = equivalent_label_array[label]
                    
    def create_connected_components(self):
        for row_i in range(0,self.binary_image.shape[0]):
            for col_i in range(0,self.binary_image.shape[1]):
                if self.binary_image[row_i,col_i] == False:
                    continue # current pixel is background
                label = self.label_matrix[row_i,col_i]
                cur_point = self.point_t(row=row_i,col=col_i)
                
                if label not in self.label_cc_map:
                    bbox = self.bbox_t(row_min=row_i, row_max=row_i, col_min=col_i, col_max=col_i)
                    self.label_cc_map[label] = self.connected_component_t(points=[cur_point],stroke_width_mean=np.nan, \
                                            stroke_width_std=np.nan, bounding_box=bbox, text_possible_flag=False)
                else:
                    list_points = self.label_cc_map[label].points
                    list_points.append(cur_point)
                    bbox = self.label_cc_map[label].bounding_box
                    if row_i < bbox.row_min:
                        bbox = bbox._replace(row_min = row_i)
                    if row_i > bbox.row_max:
                        bbox = bbox._replace(row_max = row_i)
                    if col_i < bbox.col_min:
                        bbox = bbox._replace(col_min = col_i)
                    if col_i > bbox.col_max:
                        bbox = bbox._replace(col_max = col_i)
                    self.label_cc_map[label] = self.label_cc_map[label]._replace(points = list_points, bounding_box = bbox)
    
    def stroke_width_transform(self):
        self.compute_stroke_width()
        self.compute_connected_component_stats()
        self.connected_component_verification()
        
    def compute_stroke_width(self):
        # 1st pass of SWT
        for row in range(0,self.binary_image.shape[0]):
            for col in range(0,self.binary_image.shape[1]):
                if self.binary_image[row,col] == False:
                    continue # current pixel is background
                # horizontal direction
                if (col == 0) or (self.binary_image[row,col-1] == False):
                    # edge with gradient in horizontal direction
                    opp_col = col+1
                    while (opp_col < self.binary_image.shape[1]) and (self.binary_image[row,opp_col] == True):
                        opp_col += 1
                    stroke_width = opp_col - col
                    for col_index in range(col,opp_col):
                        if stroke_width < self.swt_matrix[row,col_index]:
                            self.swt_matrix[row,col_index] = stroke_width
                            
                # vertical direction
                if (row == 0) or (self.binary_image[row-1,col] == False):
                    # edge with gradient in vertical direction
                    opp_row = row+1;
                    while (opp_row < self.binary_image.shape[0]) and (self.binary_image[opp_row,col] == True):
                        opp_row += 1
                    stroke_width = opp_row - row
                    for row_index in range(row,opp_row):
                        if stroke_width < self.swt_matrix[row_index,col]:
                            self.swt_matrix[row_index,col] = stroke_width
                            
                # diagonal directions
                if (row > 0) and (col > 0) and (self.binary_image[row-1,col-1] == False) and self.binary_image[row,col-1] and \
                    self.binary_image[row-1,col]:
                    # edge with gradient towards 4th quadrant
                    opp_index = 1
                    while (row+opp_index < self.binary_image.shape[0]) and (col+opp_index < self.binary_image.shape[1]) and \
                        self.binary_image[row+opp_index,col+opp_index]:
                        opp_index += 1
                    stroke_width = opp_index
                    for incr_index in range(1,opp_index):
                        if stroke_width < self.swt_matrix[row+incr_index,col+incr_index]:
                            self.swt_matrix[row+incr_index,col+incr_index] = stroke_width
                            
                if (col < self.binary_image.shape[1]-1) and (row > 0) and (self.binary_image[row-1,col+1] == False) and \
                    self.binary_image[row-1,col] and self.binary_image[row,col+1]:
                    # edge with gradient towards 3rd quadrant
                    opp_index = 1
                    while (row+opp_index < self.binary_image.shape[0]) and (col >= opp_index) and self.binary_image[row+opp_index,col-opp_index]:
                        opp_index += 1
                    stroke_width = opp_index
                    for incr_index in range(1,opp_index):
                        if stroke_width < self.swt_matrix[row+incr_index,col-incr_index]:
                            self.swt_matrix[row+incr_index,col-incr_index] = stroke_width
                    
        # 2nd pass (median)
        swt_final_image = self.swt_matrix
        
        for row in range(0,self.binary_image.shape[0]):
            for col in range(0,self.binary_image.shape[1]):
                if self.binary_image[row,col] == False:
                    continue # current pixel is background
                # horizontal direction
                if (col == 0) or (self.binary_image[row,col-1] == False):
                    # edge with gradient in horizontal direction
                    label_array = [self.swt_matrix[row,col]]
                    opp_col = col+1
                    while (opp_col < self.binary_image.shape[1]) and (self.binary_image[row,opp_col] == True):
                        label_array.append(self.swt_matrix[row,opp_col])
                        opp_col += 1
                    median_label = np.median(label_array)
                    for col_index in range(col,opp_col):
                        if median_label < swt_final_image[row,col_index]:
                            swt_final_image[row,col_index] = median_label
                            
                # vertical direction
                if (row == 0) or (self.binary_image[row-1,col] == False):
                    # edge with gradient in vertical direction
                    label_array = [self.swt_matrix[row,col]]
                    opp_row = row+1;
                    while (opp_row < self.binary_image.shape[0]) and (self.binary_image[opp_row,col] == True):
                        label_array.append(self.swt_matrix[opp_row,col])
                        opp_row += 1
                    median_label = np.median(label_array)
                    for row_index in range(row,opp_row):
                        if median_label < swt_final_image[row_index,col]:
                            swt_final_image[row_index,col] = median_label
                            
                # diagonal directions
                if (row > 0) and (col > 0) and (self.binary_image[row-1,col-1] == False) and self.binary_image[row,col-1] \
                    and self.binary_image[row-1,col]:
                    # edge with gradient towards 4th quadrant
                    label_array = [self.swt_matrix[row,col]]
                    opp_index = 1
                    while (row+opp_index < self.binary_image.shape[0]) and (col+opp_index < self.binary_image.shape[1]) \
                        and self.binary_image[row+opp_index,col+opp_index]:
                        label_array.append(self.swt_matrix[row+opp_index,col+opp_index])
                        opp_index += 1
                    median_label = np.median(label_array)
                    for incr_index in range(1,opp_index):
                        if median_label < swt_final_image[row+incr_index,col+incr_index]:
                            swt_final_image[row+incr_index,col+incr_index] = median_label
                            
                if (col < self.binary_image.shape[1]-1) and (row > 0) and (self.binary_image[row-1,col+1] == False) \
                    and self.binary_image[row-1,col] and self.binary_image[row,col+1]:
                    # edge with gradient towards 3rd quadrant
                    label_array = [self.swt_matrix[row,col]]
                    opp_index = 1
                    while (row+opp_index < self.binary_image.shape[0]) and (col >= opp_index) and self.binary_image[row+opp_index,col-opp_index]:
                        label_array.append(self.swt_matrix[row+opp_index,col-opp_index])
                        opp_index += 1
                    median_label = np.median(label_array)
                    for incr_index in range(1,opp_index):
                        if median_label < swt_final_image[row+incr_index,col-incr_index]:
                            swt_final_image[row+incr_index,col-incr_index] = median_label
                            
        self.swt_matrix = swt_final_image
    
    def compute_connected_component_stats(self):
        for label in self.label_cc_map:
            stroke_width_array = []
            for point in self.label_cc_map[label].points:
                row = point.row
                col = point.col
                stroke_width = self.swt_matrix[row,col]
                stroke_width_array.append(stroke_width)
                
            self.label_cc_map[label] = self.label_cc_map[label]._replace(stroke_width_mean = np.mean(stroke_width_array), \
                                    stroke_width_std = np.std(stroke_width_array))
                                    
    def connected_component_verification(self):
        # now check for the possibility of the connected component being part of text
        for label in self.label_cc_map:
            if len(self.label_cc_map[label].points) < 5:
                continue # insignificant connected component
            if self.label_cc_map[label].stroke_width_std > 0.5*self.label_cc_map[label].stroke_width_mean:
                continue # stroke width variance is too high to be a text component
            bbox = self.label_cc_map[label].bounding_box
            width = bbox.col_max - bbox.col_min + 1
            height = bbox.row_max - bbox.row_min + 1
            if (height/width < 1./10.) or (height/width > 10.):
                continue # aspect ratio suggests that this component is unlikely a text component
            # now check how many other connected components are inside the current connected component
            count_internal_cc = 0
            for other_label in self.label_cc_map:
                if other_label == label:
                    continue
                bbox_other = self.label_cc_map[other_label].bounding_box
                if (bbox.row_min < bbox_other.row_min) and (bbox.row_max > bbox_other.row_max) and \
                    (bbox.col_min < bbox_other.col_min) and (bbox.col_max > bbox_other.col_max):
                    count_internal_cc += 1
            
            if count_internal_cc < 3:
                self.label_cc_map[label] = self.label_cc_map[label]._replace(text_possible_flag = True)
                
    def create_text_image(self):
        for label in self.label_cc_map:
            if self.label_cc_map[label].text_possible_flag == False:
                continue # non-text connected component
            for point in self.label_cc_map[label].points:
                row = point.row
                col = point.col
                self.text_image[row,col] = 255
                
class ocr:
    def __init__(self):
        self.api = tesseract.TessBaseAPI()
        self.api.Init(".","eng",tesseract.OEM_DEFAULT)
        self.api.SetPageSegMode(tesseract.PSM_AUTO)
        
    def extract_text(self,text_img_file):
        image = cv.LoadImage(text_img_file, cv.CV_LOAD_IMAGE_GRAYSCALE)
        tesseract.SetCvImage(image,self.api)
        text = self.api.GetUTF8Text()
        conf = self.api.MeanTextConf()
        #print "reached extract_text() end"
        print text
        
if __name__ == "__main__":
    import sys
    img_file = sys.argv[1]
    
    if ocr_flag:
       ocr_obj = ocr()
    '''
    sub_image_array = create_sub_image(img_file,0.9,1.0,0.5,1.0) # Net Wt 7 Oz
    text_extraction_obj = text_extraction(sub_image_array)
    text_extraction_obj.process()
    if ocr_flag:
        ocr_obj.extract_text('out.png')
    '''    
    sub_image_array = create_sub_image(img_file,0.7,1.0,0.0,0.25) # 18 serving cups
    text_extraction_obj = text_extraction(sub_image_array)
    text_extraction_obj.process()
    if ocr_flag:
        ocr_obj.extract_text('out.png')
    