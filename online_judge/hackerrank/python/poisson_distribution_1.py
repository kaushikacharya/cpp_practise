# https://www.hackerrank.com/challenges/poisson-distribution-1/problem

from math import e

k = 5
mean_val = 2.5

numerator = pow(mean_val, k) * pow(e, -1*mean_val)
denom = reduce((lambda x,y: x*y), range(1,k+1))

result = numerator/denom

print "{0:.3f}".format(result)