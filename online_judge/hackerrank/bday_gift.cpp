// https://www.hackerrank.com/challenges/bday-gift
// Mar 20, 2017

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

class Solution
{
public:
    Solution(){}
    ~Solution(){}

    double compute_expectation(unsigned int N)
    {
        double expected_val = 0.0;

        for (unsigned int i = 0; i != N; ++i)
        {
            unsigned int cur_number_on_ball;
            cin >> cur_number_on_ball;
            expected_val += ((double)cur_number_on_ball) * 0.5;
            // cout << "current expected_val: " << expected_val << endl;
        }

        return expected_val;
    }

};

int main()
{
    // unsigned int max_int = numeric_limits<unsigned int>::max();
    // cout << "max unsigned int: " << max_int << endl;

    Solution sln;
    unsigned int N;
    cin >> N;
    double expected_val = sln.compute_expectation(N);
    cout << fixed << setprecision(1) << expected_val << endl;
    return 0;
}
