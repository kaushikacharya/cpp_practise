from math import exp
from math import log

gamma = 0.5772

class hangover:
    def __init__(self):
        self.anamolous_dict_sum_to_k = {}
        self.initialize_anamolous_dict_sum_to_k()
        
    def initialize_anamolous_dict_sum_to_k(self):
        # This stores the sum of those k where sum and sum(based on eqn) are different at rounded by 2 decimal places
        anamolous_dict_sum_to_k = {}
        anamolous_dict_sum_to_k[1.00] = 1
        anamolous_dict_sum_to_k[1.50] = 2
        anamolous_dict_sum_to_k[1.83] = 3
        anamolous_dict_sum_to_k[2.08] = 4
        anamolous_dict_sum_to_k[2.28] = 5
        anamolous_dict_sum_to_k[3.99] = 30
        self.anamolous_dict_sum_to_k = anamolous_dict_sum_to_k
        
    def find_k(self,input_sum):
        # input_sum is always rounded to 2 decimal place
        sum = input_sum + 1
        final_k = None # it should correspond to input_sum not sum
        
        if 2.28 < sum:
            if sum in self.anamolous_dict_sum_to_k:
                final_k = self.anamolous_dict_sum_to_k[sum] - 1
            else:
                k = int(exp(sum - gamma))
                while True:
                    sum_k_eqn_low = log(k) + gamma + 1.0/(2*k)
                    sum_k_eqn_high = log(k+1) + gamma + 1.0/(2*(k+1))
                    if sum_k_eqn_low < sum:
                        if sum <= sum_k_eqn_high:
                            final_k = k
                            break
                        else:
                            # go higher
                            k += 1
                    else:
                        k -= 1
        else:
            if 1.50 < sum:
                if 1.83 < sum:
                    if 2.08 < sum:
                        final_k = 4
                    else:
                        final_k = 3
                else:
                    final_k = 2
            else:
                final_k = 1
          
        assert (final_k != None), 'final_k not assigned'
        return final_k

if __name__ == "__main__":
    import sys
    hangover_obj = hangover()