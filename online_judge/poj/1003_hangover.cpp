// http://poj.org/problem?id=1003
// http://poj.org/showmessage?message_id=156385
// http://en.wikipedia.org/wiki/Harmonic_series_%28mathematics%29
// http://www.cplusplus.com/forum/beginner/19089/

//#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
#include <cassert>

#define GAMMA 0.5772

class Hangover
{
public:
    Hangover();
    ~Hangover();
public:
    int find_k(float input_sum);
private:
    void initialize_anamolous_dict();
    std::map<float,int> anamolous_dict_sum_to_k_;
};

Hangover::Hangover()
{
    initialize_anamolous_dict();
}
Hangover::~Hangover()
{
    //delete anamolous_dict_sum_to_k_;
}

void Hangover::initialize_anamolous_dict()
{
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(1.00,1));
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(1.50,2));
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(1.83,3));
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(2.08,4));
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(2.28,5));
    anamolous_dict_sum_to_k_.insert(std::make_pair<float,int>(3.99,30));
}

// sum_k:
/*
 * sum_k = 0
    for j in range(1,k+1):
        sum_k += 1.0/j
 */
// sum_eqn_k: log(k) + gamma + 1.0/(2*k)
// input_sum: its as mentioned in the problem
int Hangover::find_k(float input_sum)
{
    float sum = input_sum + 1;
    int final_k = 0; // it should correspond to input_sum not sum

    if (2.28 < sum)
    {
        std::map<float,int>::iterator it = anamolous_dict_sum_to_k_.find(sum);

        if (it == anamolous_dict_sum_to_k_.end())
        {
            int k = (int)(exp(sum - GAMMA));
            while (true)
            {
                float sum_k_eqn_low = log(1.0*k) + GAMMA + 1.0/(2*k);
                float sum_k_eqn_high = log(1.0*(k+1)) + GAMMA + 1.0/(2*(k+1));

                if (sum_k_eqn_low < sum)
                {
                    if (sum <= sum_k_eqn_high)
                    {
                        final_k = k;
                        break;
                    }
                    else
                    {
                        // go higher
                        ++k;
                    }
                }
                else
                {
                    --k;
                }
            }
        }
        else
        {
            final_k = (*it).second - 1;
        }
    }
    else
    {
        // These cases sum_k and sum_eqn_k shows difference when rounded to 2 decimal points.
        // Hence decision is taken based on sum_k
        if (1.50 < sum)
        {
            if (1.83 < sum)
            {
                if (2.08 < sum  )
                {
                    final_k = 4;
                }
                else
                {
                    final_k = 3;
                }
            }
            else
            {
                final_k = 2;
            }
        }
        else
        {
            final_k = 1;
        }
    }

    assert((final_k > 0) && "final_k not assigned");
    return final_k; // Remove later
}

int main(int argc, char* argv[])
{
    Hangover hangOver;
    float input_sum;

    while (scanf("%f",&input_sum))
    {
        if (input_sum == 0.00)
        {
            break;
        }
        else
        {
            printf( "%d card(s)\n",hangOver.find_k(input_sum) );
        }
    }

    //printf("%d\n",hangOver.find_k(atof(argv[1])) );
    //scanf("%d %d", &a, &b);
    return 0;
}

