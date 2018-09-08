# https://www.hackerrank.com/challenges/poisson-distribution-2/problem

from math import e

mean_A = 0.88
mean_B = 1.55

# For Poisson distribution, mean = variance = lambda
var_A = mean_A
var_B = mean_B

# We will be the following formula:
# variance = E[X^2] - (E[X])^2

expected_cost_A = 160 + 40*(var_A + mean_A**2)
expected_cost_B = 128 + 40*(var_B + mean_B**2)

print "{0:.3f}".format(expected_cost_A)
print "{0:.3f}".format(expected_cost_B)


"""
Reference:
    https://onlinecourses.science.psu.edu/stat414/node/83/
"""