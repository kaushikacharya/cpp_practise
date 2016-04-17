// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
// Date: Feb 08, 2015

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Dynamic Programming based solution: Time complexity: O(n^2)
template <typename T>
class SolutionDP
{
public:
    SolutionDP(){}

    int compute_LIS(vector<T>& inputVec)
    {
        vector<int> vecLIS;
        vecLIS.reserve(inputVec.size());

        vecLIS.push_back(1);
        for (int i = 1; i != inputVec.size(); ++i)
        {
            int max_LIS_ending_at_pos_i = 1;
            for (int j=0; j != i; ++j)
            {
                if (inputVec[j] < inputVec[i])
                {
                    if (max_LIS_ending_at_pos_i < (1+vecLIS[j]))
                    {
                        max_LIS_ending_at_pos_i = 1+vecLIS[j];
                    }
                }
            }
            vecLIS.push_back(max_LIS_ending_at_pos_i);
        }

        return *max_element(vecLIS.begin(), vecLIS.end());
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    SolutionDP<int> sln;
    int val_LIS = sln.compute_LIS(vec);
    cout << val_LIS << endl;

    return 0;
}

/*
http://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithms
TBD: Implement the better complexity algo mentioned in wiki
*/
