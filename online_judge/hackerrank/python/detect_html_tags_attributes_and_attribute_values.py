# https://www.hackerrank.com/challenges/detect-html-tags-attributes-and-attribute-values/problem
# 15th Aug 2018

from HTMLParser import HTMLParser


class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print "{0}".format(tag)
        for attr_tuple in attrs:
            attr_key, attr_value = attr_tuple
            print "-> {0} > {1}".format(attr_key, attr_value)

html = ""
n = int(raw_input())
for i in range(n):
    html += raw_input()
    html += "\n"

parser = MyHTMLParser()
parser.feed(data=html)
