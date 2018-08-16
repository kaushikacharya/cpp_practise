# https://www.hackerrank.com/challenges/introduction-to-regex/problem
# Aug 16th 2018

import re

T = int(raw_input())

for i in range(T):
    input_str = raw_input()
    if re.match(pattern=r'^[+-]?[\d]*[.]{1}[\d]+$', string=input_str):
        print "True"
    else:
        print "False"

"""
Learning:
    1. re.match finds match if it occurs at start of the string.
    2. Use bool to print True, False
"""
