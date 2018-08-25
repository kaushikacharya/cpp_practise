# https://www.hackerrank.com/challenges/xml2-find-the-maximum-depth/problem
# Aug 25th 2018

import xml.etree.ElementTree as etree

maxdepth = 0


def depth(elem, level):
    global maxdepth

    if maxdepth < (level + 1):
        maxdepth = level + 1

    # print "tag: {0} :: level: {1}".format(elem.tag, level)
    for child_elem in list(elem):
        depth(child_elem, level=level+1)

if __name__ == "__main__":
    n = int(raw_input())
    xml = ""
    for i in range(n):
        xml = xml + raw_input() + "\n"
    tree = etree.ElementTree(etree.fromstring(xml))
    depth(tree.getroot(), -1)
    print maxdepth
