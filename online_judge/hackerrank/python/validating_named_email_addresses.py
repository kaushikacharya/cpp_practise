# Enter your code here. Read input from STDIN. Print output to STDOUT
# Aug 09th 2018

import email.utils
import re

n = int(raw_input())

for i in range(n):
    input_str = raw_input()
    person_name, email_address = email.utils.parseaddr(input_str)
    
    # https://stackoverflow.com/questions/13989640/regular-expression-to-match-a-dot
    # This explains that dot is a metacharacter and that's the reason for failure in 1st submisson
    # m = re.match(pattern=r'^[a-z]{1}[a-z0-9_.-]+@[a-z]+.[a-z]{1,3}$', string=email_address, flags=re.I)
    m = re.match(pattern=r'^[a-z]{1}[a-z0-9_.-]+@[a-z]+[.]+[a-z]{1,3}$', string=email_address, flags=re.I)
    
    if m:
        print email.utils.formataddr((person_name, email_address))
    

"""
Note the alternative of [a-z0-9_.-] i.e. [\w\-\.]
    Escape being used.
"""