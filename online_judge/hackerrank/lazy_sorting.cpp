//
// Mar 08, 2017

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    Solution(int n, vector<int> vecElem)
        : n_(n)
        {
            vecElem_.reserve(n);
            for (vector<int>::iterator it = vecElem.begin(); it != vecElem.end(); ++it)
            {
                vecElem_.push_back(*it);
            }

            vecFactorial_.push_back(1.0);
        }

    double compute_expectation()
    {
        // If the elements are already in sorted order then expectation = 0
        bool flag_sorted = is_vector_sorted();
        if (flag_sorted)
        {
            return 0.0;
        }
        // This is the geometric series: 1/(1-x)^2 where x = prob_of_permutation
        double prob_of_permutation = compute_probability_of_ordered_permutation();
        //cout << "prob_of_permutation: " << prob_of_permutation << endl;
        // cout << "1/prob_of_permutation: " << 1.0/prob_of_permutation << endl;
        return 1.0/prob_of_permutation;

        /*
        // Issue with following approach is that we won't be sure at which i to stop
        double epsilon = 0.00000001;
        double expected_val = 0.0;
        double prob_failure_till_now = 1.0;

        int i = 1;
        while (true)
        {
            // product of failure probability till now(i.e. permutation which is non-decreasing till last step) and success probability
            double prob_success_now = prob_failure_till_now*prob_of_permutation;
            double cur_val = double(i)*prob_success_now;

            if (cur_val < epsilon)
            {
                break;
            }
            else
            {
                expected_val += cur_val;
                prob_failure_till_now *= (1.0 - prob_of_permutation);
                ++i;
            }
        }

        cout << "i: " << i << endl;
        return expected_val;
        */
    }
private:
    double compute_probability_of_ordered_permutation()
    {
        sort(vecElem_.begin(), vecElem_.end());
        double denom = compute_factorial(n_);
        double num = 1.0;

        int prevElem = vecElem_.front();
        int curElem = prevElem;
        unsigned int prevCount = 1;

        for (vector<int>::iterator it = vecElem_.begin()+1; it != vecElem_.end(); ++it)
        {
            curElem = *it;

            if (curElem == prevElem)
            {
                ++prevCount;
            }
            else
            {
                if (prevCount > 1)
                {
                    double factorial = compute_factorial(prevCount);
                    num *= factorial;
                    // cout << "elem: " << prevElem << " :: count: " << prevCount << " :: factorial: " << factorial << endl;
                }
                prevCount = 1; // reset
                prevElem = curElem;

            }
        }
        if (prevCount > 1)
        {
            double factorial = compute_factorial(prevCount);
            num *= factorial;
            // cout << "elem: " << prevElem << " :: count: " << prevCount << " :: factorial: " << factorial << endl;
        }

        double prob = num/denom;
        return prob;
    }

    // output type double: as we would use for computing probability of non-decreasing sequence
    double compute_factorial(int n)
    {
        int i = vecFactorial_.size();
        while (i < n)
        {
            double val = vecFactorial_[i-1]*(i+1);
            vecFactorial_.push_back(val);
            ++i;
        }
        return vecFactorial_[n-1];
    }

    bool is_vector_sorted()
    {
        int prevElem = vecElem_.front();
        bool flag_sorted = true;

        for (vector<int>::iterator it = vecElem_.begin()+1; it != vecElem_.end(); ++it)
        {
            int curElem = *it;

            if (curElem < prevElem)
            {
                flag_sorted = false;
                break;
            }
            prevElem = curElem;
        }

        return flag_sorted;
    }
private:
    int n_;
    vector<int> vecElem_;
    vector<double> vecFactorial_;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    bool flag_read_from_stdin = true;

    if (flag_read_from_stdin)
    {
        cin >> n;
        vector<int> vecElem;
        vecElem.reserve(n);
        for (unsigned int i=0; i != n; ++i)
        {
            int elem;
            cin >> elem;
            vecElem.push_back(elem);
        }

        Solution sln(n, vecElem);
        double expected_value = sln.compute_expectation();
        cout << fixed << setprecision(6) << expected_value << endl;
    }
    else
    {
        n = 2;
        int arrElem[2] = {2,5};
        //int arrElem[4] = {7,12,10,9};
        //int arrElem[15] = {5, 2, 19, 15, 19, 23, 6, 11, 2, 18, 6, 30, 28, 5, 12};
        vector<int> vecElem(arrElem, arrElem + sizeof(arrElem)/sizeof(arrElem[0]));

        Solution sln(n, vecElem);
        double expected_value = sln.compute_expectation();
        cout << "expected value: " << fixed << setprecision(6) << expected_value << endl;
    }

    return 0;
}

/*
https://en.wikipedia.org/wiki/Taylor_series#List_of_Maclaurin_series_of_some_common_functions

Better way to solve: expected number = number of permutations
            No need to compute probability and then inverse it.
*/
