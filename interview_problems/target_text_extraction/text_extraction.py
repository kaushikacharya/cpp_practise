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

def show_sub_image(img):
    plt.figure()
    plt.imshow(img,cmap=plt.cm.gray)
    plt.axis('off')
    plt.show()
    
def smooth_with_function_and_mask(image, function, mask):
    # taken from _canny.py
    bleed_over = function(mask.astype(float))
    masked_image = np.zeros(image.shape, image.dtype)
    masked_image[mask] = image[mask]
    smoothed_image = function(masked_image)
    output_image = smoothed_image / (bleed_over + np.finfo(float).eps)
    return output_image
    
def connected_component_labeling(binary_image):
    # 8-connectivity based
    # two-pass algorithm
    label_image = np.zeros(binary_image.shape, int)
    
    label_count = 0;
    equivalent_label_array = [0]
    # 1st pass
    for row in range(0,binary_image.shape[0]):
        for col in range(0,binary_image.shape[1]):
            if binary_image[row,col] == False:
                continue # current pixel is background
            label = 0
            if row > 0:
                # check north-west, north and north-east neighbours
                for col_shift in range(-1,2):
                    if ((col + col_shift) < 0) or ((col + col_shift) >= binary_image.shape[1]):
                        continue
                    if binary_image[row-1,col + col_shift] == True:
                        label_neighbour = label_image[row-1,col + col_shift]
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
                if binary_image[row,col-1] == True:
                    label_neighbour = label_image[row,col-1]
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
            label_image[row,col] = label
            
    print('label_count: %d\n' % (label_count)) 
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
                
    print('equivalent_label_array: %s\n' % (equivalent_label_array))
    equivalent_label_set = list(set(equivalent_label_array))
    print('label_count(unique): %d\n' % (len(equivalent_label_set)))
                
    # 2nd pass
    for row in range(0,binary_image.shape[0]):
        for col in range(0,binary_image.shape[1]):
            if binary_image[row,col] == False:
                continue # current pixel is background
            label = label_image[row,col]
            if equivalent_label_array[label] != label:
                label_image[row,col] = equivalent_label_array[label]
                
    point_t = namedtuple('point','row col')
    bbox_t = namedtuple('bbox','row_min row_max col_min col_max')
    connected_component_t = namedtuple('connected_component','points stroke_width_mean stroke_width_std bounding_box text_possible_flag')
    label_cc_map = {}
    # connected components
    #sum_count = 0
    #cur_point = point_t(row=0, col=0)
    for row_i in range(0,binary_image.shape[0]):
        for col_i in range(0,binary_image.shape[1]):
            if binary_image[row_i,col_i] == False:
                continue # current pixel is background
            label = label_image[row_i,col_i]
            cur_point = point_t(row=row_i,col=col_i)
            
            if label not in label_cc_map:
                bbox = bbox_t(row_min=row_i, row_max=row_i, col_min=col_i, col_max=col_i)
                label_cc_map[label] = connected_component_t(points=[cur_point],stroke_width_mean=np.nan, \
                                        stroke_width_std=np.nan, bounding_box=bbox, text_possible_flag=False)
                #label_cc_map[label] = label_cc_map[label].points.append(cur_point)
            else:
                #sum_count += 1
                list_points = label_cc_map[label].points
                list_points.append(cur_point)
                bbox = label_cc_map[label].bounding_box
                if row_i < bbox.row_min:
                    bbox = bbox._replace(row_min = row_i)
                if row_i > bbox.row_max:
                    bbox = bbox._replace(row_max = row_i)
                if col_i < bbox.col_min:
                    bbox = bbox._replace(col_min = col_i)
                if col_i > bbox.col_max:
                    bbox = bbox._replace(col_max = col_i)
                label_cc_map[label] = label_cc_map[label]._replace(points = list_points, bounding_box = bbox)
    
    #print('sum_count: %d\n' % (sum_count))
    # stroke width transform(SWT)
    swt_image = np.zeros(binary_image.shape, int)
    swt_image += (binary_image.shape[0]+binary_image.shape[1])
    
    # 1st pass of SWT
    for row in range(0,binary_image.shape[0]):
        for col in range(0,binary_image.shape[1]):
            if binary_image[row,col] == False:
                continue # current pixel is background
            # horizontal direction
            if (col == 0) or (binary_image[row,col-1] == False):
                # edge with gradient in horizontal direction
                opp_col = col+1
                while (opp_col < binary_image.shape[1]) and (binary_image[row,opp_col] == True):
                    opp_col += 1
                stroke_width = opp_col - col
                for col_index in range(col,opp_col):
                    if stroke_width < swt_image[row,col_index]:
                        swt_image[row,col_index] = stroke_width
                        
            # vertical direction
            if (row == 0) or (binary_image[row-1,col] == False):
                # edge with gradient in vertical direction
                opp_row = row+1;
                while (opp_row < binary_image.shape[0]) and (binary_image[opp_row,col] == True):
                    opp_row += 1
                stroke_width = opp_row - row
                for row_index in range(row,opp_row):
                    if stroke_width < swt_image[row_index,col]:
                        swt_image[row_index,col] = stroke_width
                        
            # diagonal directions
            if (row > 0) and (col > 0) and (binary_image[row-1,col-1] == False) and binary_image[row,col-1] and \
                binary_image[row-1,col]:
                # edge with gradient towards 4th quadrant
                opp_index = 1
                while (row+opp_index < binary_image.shape[0]) and (col+opp_index < binary_image.shape[1]) and \
                    binary_image[row+opp_index,col+opp_index]:
                    opp_index += 1
                stroke_width = opp_index
                for incr_index in range(1,opp_index):
                    if stroke_width < swt_image[row+incr_index,col+incr_index]:
                        swt_image[row+incr_index,col+incr_index] = stroke_width
                        
            if (col < binary_image.shape[1]-1) and (row > 0) and (binary_image[row-1,col+1] == False) and \
                binary_image[row-1,col] and binary_image[row,col+1]:
                # edge with gradient towards 3rd quadrant
                opp_index = 1
                while (row+opp_index < binary_image.shape[0]) and (col >= opp_index) and binary_image[row+opp_index,col-opp_index]:
                    opp_index += 1
                stroke_width = opp_index
                for incr_index in range(1,opp_index):
                    if stroke_width < swt_image[row+incr_index,col-incr_index]:
                        swt_image[row+incr_index,col-incr_index] = stroke_width
                
    # 2nd pass (median)
    swt_final_image = swt_image
    
    for row in range(0,binary_image.shape[0]):
        for col in range(0,binary_image.shape[1]):
            if binary_image[row,col] == False:
                continue # current pixel is background
            # horizontal direction
            if (col == 0) or (binary_image[row,col-1] == False):
                # edge with gradient in horizontal direction
                label_array = [swt_image[row,col]]
                opp_col = col+1
                while (opp_col < binary_image.shape[1]) and (binary_image[row,opp_col] == True):
                    label_array.append(swt_image[row,opp_col])
                    opp_col += 1
                median_label = np.median(label_array)
                for col_index in range(col,opp_col):
                    if median_label < swt_final_image[row,col_index]:
                        swt_final_image[row,col_index] = median_label
                        
            # vertical direction
            if (row == 0) or (binary_image[row-1,col] == False):
                # edge with gradient in vertical direction
                label_array = [swt_image[row,col]]
                opp_row = row+1;
                while (opp_row < binary_image.shape[0]) and (binary_image[opp_row,col] == True):
                    label_array.append(swt_image[opp_row,col])
                    opp_row += 1
                median_label = np.median(label_array)
                for row_index in range(row,opp_row):
                    if median_label < swt_final_image[row_index,col]:
                        swt_final_image[row_index,col] = median_label
                        
            # diagonal directions
            if (row > 0) and (col > 0) and (binary_image[row-1,col-1] == False) and binary_image[row,col-1] \
                and binary_image[row-1,col]:
                # edge with gradient towards 4th quadrant
                label_array = [swt_image[row,col]]
                opp_index = 1
                while (row+opp_index < binary_image.shape[0]) and (col+opp_index < binary_image.shape[1]) \
                    and binary_image[row+opp_index,col+opp_index]:
                    label_array.append(swt_image[row+opp_index,col+opp_index])
                    opp_index += 1
                median_label = np.median(label_array)
                for incr_index in range(1,opp_index):
                    if median_label < swt_final_image[row+incr_index,col+incr_index]:
                        swt_final_image[row+incr_index,col+incr_index] = median_label
                        
            if (col < binary_image.shape[1]-1) and (row > 0) and (binary_image[row-1,col+1] == False) \
                and binary_image[row-1,col] and binary_image[row,col+1]:
                # edge with gradient towards 3rd quadrant
                label_array = [swt_image[row,col]]
                opp_index = 1
                while (row+opp_index < binary_image.shape[0]) and (col >= opp_index) and binary_image[row+opp_index,col-opp_index]:
                    label_array.append(swt_image[row+opp_index,col-opp_index])
                    opp_index += 1
                median_label = np.median(label_array)
                for incr_index in range(1,opp_index):
                    if median_label < swt_final_image[row+incr_index,col-incr_index]:
                        swt_final_image[row+incr_index,col-incr_index] = median_label
    
    
    # compute stats of components
    for label in label_cc_map:
        stroke_width_array = []
        for point in label_cc_map[label].points:
            row = point.row
            col = point.col
            stroke_width = swt_final_image[row,col]
            stroke_width_array.append(stroke_width)
            
        label_cc_map[label] = label_cc_map[label]._replace(stroke_width_mean = np.mean(stroke_width_array), \
                                stroke_width_std = np.std(stroke_width_array))
                                
    # now check for the possibility of the connected component being part of text
    for label in label_cc_map:
        if label_cc_map[label].stroke_width_std > 0.5*label_cc_map[label].stroke_width_mean:
            continue
        bbox = label_cc_map[label].bounding_box
        width = bbox.col_max - bbox.col_min + 1
        height = bbox.row_max - bbox.row_min + 1
        if (height/width < 1./10.) or (height/width > 10.):
            continue
        # now check how many other connected components are inside the current connected component
        count_internal_cc = 0
        for other_label in label_cc_map:
            if other_label == label:
                continue
            bbox_other = label_cc_map[other_label].bounding_box
            if (bbox.row_min < bbox_other.row_min) and (bbox.row_max > bbox_other.row_max) and \
                (bbox.col_min < bbox_other.col_min) and (bbox.col_max > bbox_other.col_max):
                count_internal_cc += 1
        
        if count_internal_cc < 3:
            label_cc_map[label] = label_cc_map[label]._replace(text_possible_flag = True)
    
    # now write the binary image where text is the white foreground
    text_image = np.zeros(binary_image.shape,np.uint8) #np.dtype('float64')
    for label in label_cc_map:
        if label_cc_map[label].text_possible_flag == False:
            continue # non-text connected component
        for point in label_cc_map[label].points:
            row = point.row
            col = point.col
            text_image[row,col] = 255
    
    #imsave('out.png',text_image)
    plt.imshow(text_image)
    plt.savefig('out.png')
    return text_image
            
    
def process_sub_image(img,sigma=1.):
    if img.ndim == 3:
        img = rgb2gray(img)
    edges = filter.canny(img)
    #show_sub_image(edges)
    
    low_threshold = 0.1 * dtype_limits(img)[1]
    high_threshold = 0.2 * dtype_limits(img)[1]
    mask = np.ones(img.shape, dtype=bool)
    fsmooth = lambda x: gaussian_filter(x, sigma, mode='constant')
    smoothed = smooth_with_function_and_mask(img, fsmooth, mask)
    jsobel = ndi.sobel(smoothed, axis=1)
    isobel = ndi.sobel(smoothed, axis=0)
    
    thresh = filter.threshold_otsu(img)
    binary = img > thresh
    #show_sub_image(binary)
    return connected_component_labeling(binary)
    # return binary
    

if __name__ == "__main__":
    import sys
    img_file = sys.argv[1]
    img_array = imread(img_file)
    img = img_as_float(img_array)
    #show_sub_image(img)
    #text_image = process_sub_image(img[660:770,40:170]) # 18 serving cups
    text_image = process_sub_image(img[720:770,450:710]) # Net Wt 7 Oz
    
'''
http://scikit-image.org/docs/0.9.x/auto_examples/plot_template.html
shows how to select subimage

http://scikit-image.org/docs/dev/auto_examples/plot_otsu.html
http://en.wikipedia.org/wiki/Connected-component_labeling

http://stackoverflow.com/questions/13811334/saving-numpy-ndarray-in-python-as-an-image
'''