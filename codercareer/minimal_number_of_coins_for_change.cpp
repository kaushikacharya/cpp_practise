// http://codercareer.blogspot.in/2011/12/no-26-minimal-number-of-coins-for.html
// http://www.algorithmist.com/index.php/Min-Coin_Change
// Date: Feb 15, 2015

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution
{
public:
    int compute_change(int total, vector<int>& vecCoin)
    {
        if (vecCoin.empty())
        {
            return 0;
        }
        vector<int> vecCount(total, numeric_limits<int>::max());

        for (unsigned int coin_i = 0; coin_i != vecCoin.size(); ++coin_i)
        {
            // compute min number of coins using vecCoin[0,....,coin_i]
            int coin = vecCoin[coin_i];
            for (int val=coin-1; val != total; ++val)
            {
                if (val == (coin-1))
                {
                    vecCount[val] = 1;
                }
                else
                {
                    // update if considering coin can reduce the minimal number of coins for change of val
                    if (vecCount[val-coin] < numeric_limits<int>::max())
                    {
                        if ( (vecCount[val-coin]+1) < vecCount[val] )
                        {
                            vecCount[val] = vecCount[val-coin]+1;
                        }
                    }
                }
            }
        }

        return vecCount.back();
    }
};

int main(int argc, char* argv[])
{
    // cout << numeric_limits<int>::max() << endl;
    int arr[] = {9,1,3,10};
    int total = 15;
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Solution sln;
    int minimal_num = sln.compute_change(total, vec);
    cout << minimal_num << endl;

    return 0;
}

