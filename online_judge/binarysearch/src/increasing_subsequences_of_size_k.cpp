/**
* https://binarysearch.com/problems/Increasing-Subsequences-of-Size-K
* Dec 25, 2020
*
* Algorithm: Dynamic Programming
* Approach: Compute subsequence size k at any position of vector using subsequence size (k-1) for all the elements before it.
* Time Complexity: O(n^2)
* Space Complexity: O(n)
* Status: Fails test case of nums: 0,1,....,499  k:10
*/

#include <increasing_subsequences_of_size_k.hpp>

int modulus_sum(int x, int y){
    int mod_denom = (int)(pow(10,9) + 7);
    return (x + y) % mod_denom;
}

int solve(vector<int>& nums, int k) {
    if ((nums.size() == 0) || (k == 0)){
        return 0;
    }

    int mod_denom = (int)pow(10,9) + 7;
    cout << "INT_MAX: " << INT_MAX << endl;

    // Initialize for k=1 subsequence size. Each element of nums forms it subsequence of size=1
    vector<int> prevVec(nums.size(), 1);
    // Allocate vector for computing subsequence size=i based on prevVec which represents subsequence size=(i-1)
    vector<int> curVec(nums.size(), 0); // values doesn't matter as it will be initialized to 0 at each iteration

    cout << "\tsize(subsequence): " << 1 << " :: nSubsequences: " << accumulate(prevVec.begin(), prevVec.end(), 0, modulus_sum) << endl;

    // Iterate with subsequence size 2,...,k
    for (unsigned int i=2; i < (k+1); ++i){
        // cout << "i: " << i << endl;
        // initialize curVec elements to 0 for subsequence size i.
        fill(curVec.begin(), curVec.end(), 0);

        // Populate number of strictly increasing subsequence ending with j'th element of nums
        // Compute using the solution for subsequence size = (i-1)
        for (unsigned int j=(i-1); j < nums.size(); ++j){
            // Idea: If nums[j] > nums[u], then subsequences formed with size=(i-1) ending at u'th element can be extended to j'th element with size=i
            for (unsigned int u=0; u < j; ++u){
                if (nums[j] > nums[u]){
                    curVec[j] += prevVec[u];
                    curVec[j] %= mod_denom;
                }
            }
            // cout << "j: " << j << " :: curVec[j]: " << curVec[j] << endl;
        }

        // https://www.geeksforgeeks.org/modulus-function-in-c-stl/
        // transform(curVec.begin(), curVec.end(), curVec.begin(), bind2nd(modulus<int>(), mod_denom));

        // https://www.geeksforgeeks.org/accumulate-and-partial_sum-in-c-stl-numeric-header/
        cout << "\tsize(subsequence): " << i << " :: nSubsequences: " << accumulate(curVec.begin(), curVec.end(), 0, modulus_sum) << endl;

        // copying for next iteration with (i+1) subsequence size
        prevVec = curVec;
    }

    int nSubsequences = accumulate(prevVec.begin(), prevVec.end(), 0, modulus_sum);
    cout << "nSubsequences: " << nSubsequences << endl;


    return nSubsequences%mod_denom;
}
