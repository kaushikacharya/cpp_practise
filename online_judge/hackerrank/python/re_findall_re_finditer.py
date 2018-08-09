# Enter your code here. Read input from STDIN. Print output to STDOUT
# Aug 08th 2018

import re

input_string = raw_input()
m = re.findall(pattern=r'(?<=[qwrtypsdfghjklzxcvbnm])[aeiou]{2,}(?=[qwrtypsdfghjklzxcvbnm])', string=input_string, flags=re.I)
if len(m) > 0:
    for grp in m:
        print grp
else:
    print -1
    
    
if False:
    # !st submission. It works but the approach isn't clean.
    n_input_string = len(input_string)
    flag_group_found = False
    for m in re.finditer(r'[AEIOUaeiou]{2,}', input_string):
        span_begin, span_end = m.span()
        if span_begin > 0 and span_end < n_input_string and re.match(r'[QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm]', input_string[span_begin-1]) is not None and re.match(r'[QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm]', input_string[span_end]) is not None:
            print m.group()
            flag_group_found = True
            
    if not flag_group_found:
        print -1
        
"""
    Reference: 
        https://www.hackerrank.com/challenges/python-raw-input/tutorial
        Reading input from STDIN
"""
