// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
// Date: Feb 14, 2015

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int compute_ways_for_change(int total, vector<int>& vecCoin)
    {
        vector<int> vecWay(total, 0);

        for (unsigned int coin_i=0; coin_i != vecCoin.size(); ++coin_i)
        {
            int coin = vecCoin[coin_i];

            for (int sum=coin-1; sum != total; ++sum)
            {
                if (sum == (coin-1))
                {
                    ++vecWay[sum];
                }
                else
                {
                    vecWay[sum] += vecWay[sum-coin];
                }
            }
        }

        return vecWay.back();
    }
};

int main(int argc, char* argv[])
{
    int total = 10;
    int arr[] = {5,2,3,6};
    vector<int> vecCoin(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution sln;
    int count_ways = sln.compute_ways_for_change(total, vecCoin);
    cout << count_ways << endl;

    return 0;
}
