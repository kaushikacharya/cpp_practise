# https://www.hackerrank.com/challenges/xml-1-find-the-score/problem
# Aug 24th 2018

import sys
import xml.etree.ElementTree as etree


def get_attr_number(node):
    # your code goes here\
    n_attrib = 0
    for elem in node.iter():
        for attrib_name, attrib_val in elem.items():
            # print "attrib name: {0} :: attrib val: {1}".format(attrib_name, attrib_val)
            n_attrib += 1

    return n_attrib

if __name__ == '__main__':
    sys.stdin.readline()
    xml = sys.stdin.read()
    tree = etree.ElementTree(etree.fromstring(xml))
    root = tree.getroot()
    print get_attr_number(root)