# https://www.hackerrank.com/challenges/poisson-distribution-3/problem
# Sept 12, 2018

from math import e


def compute_prob(lambda_val, k):
    numer = pow(lambda_val, k) * pow(e, -1 * lambda_val)
    denom = reduce(lambda x, y: x * y, range(1, k + 1) if k > 0 else [1])
    prob = numer / denom
    return prob

val_lambda = 3

# (a) Find the probability that no calls come in a given 1 minute period.
prob_no_call = compute_prob(lambda_val=val_lambda, k=0)
prob_a = prob_no_call

# (b) Assume that the number of calls arriving in two different minutes are independent.
#  Find the probability that atleast two calls will arrive in a given two minute period.

# We will compute the probability of complement.

# (i) No calls in both minutes of two minute period.
# product because event in 1st minute is independent of 2nd minute in 2 minute period.

# (ii) No call in one minute but 1 call in another minute.
prob_single_call = compute_prob(lambda_val=val_lambda, k=1)

prob_b = 1 - prob_no_call*prob_no_call - 2*prob_no_call*prob_single_call

print "{0:.3f}".format(prob_a)
print "{0:.3f}".format(prob_b)

