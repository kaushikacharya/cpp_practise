# Enter your code here. Read input from STDIN. Print output to STDOUT
# https://www.hackerrank.com/challenges/html-parser-part-1
# Aug 11, 2018

from HTMLParser import HTMLParser


# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print "Start : {0}".format(tag)
        for attr_tuple in attrs:
            attr_key, attr_value = attr_tuple
            print "-> {0} > {1}".format(attr_key, attr_value if attr_value else "None")

    def handle_endtag(self, tag):
        print "End   : {0}".format(tag)

    def handle_startendtag(self, tag, attrs):
        print "Empty : {0}".format(tag)
        for attr_tuple in attrs:
            attr_key, attr_value = attr_tuple
            print "-> {0} > {1}".format(attr_key, attr_value if attr_value else "None")


# instantiate the parser
parser = MyHTMLParser()

n_lines = int(raw_input())

html_data = ""
for i in range(n_lines):
    if i == 0:
        html_data = raw_input()
    else:
        html_data += "\n" + raw_input()

parser.feed(data=html_data)

"""
https://stackoverflow.com/questions/11529273/how-to-condense-if-else-into-one-line-in-python (Levon's answer)
"""
