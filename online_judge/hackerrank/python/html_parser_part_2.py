# https://www.hackerrank.com/challenges/html-parser-part-2
# Aug 14th 2018

from HTMLParser import HTMLParser


class MyHTMLParser(HTMLParser):
    def handle_comment(self, data):
        data = data.rstrip()
        data_lines = data.split("\n")
        if len(data_lines) == 1:
            print ">>> Single-line Comment"
            if data != "":
                print "{0}".format(data)
        else:
            print ">>> Multi-line Comment"
            print "{0}".format(data)

    def handle_data(self, data):
        data = data.rstrip()
        if data == "":
            return
        print ">>> Data"
        print "{0}".format(data)

# read input html data
html = ""
for i in range(int(raw_input())):
    html += raw_input().rstrip()
    html += '\n'

parser = MyHTMLParser()
parser.feed(data=html)
