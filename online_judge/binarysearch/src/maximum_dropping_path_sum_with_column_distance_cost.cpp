/**
* Problem: Maximum Dropping Path Sum With Column Distance Cost
* URL: https://binarysearch.com/problems/Maximum-Dropping-Path-Sum-With-Column-Distance-Cost
* Date: Jan 04, 2021
*
* Time Complexity: O(n*m*m) where n is row length and m is column length.
* Space Complexity: O(n*m)
*
* Status: Time Limit Exceeded
*/

#include <maximum_dropping_path_sum_with_column_distance_cost.hpp>

using namespace std;

int solve(vector<vector<int>>& matrix) {
    int n = matrix.size();  // number of rows
    int m = matrix[0].size();  // number of columns
    // cout << "n: " << n << " :: m: " << m << endl;

    if (n == 0){
        return 0;
    }

    // Max dropping path vector till 0'th row
    // maxPathSum[j] represents the max dropping path ending at j'th column till the current row
    vector<int> maxPathSum = matrix[0];
    vector<int> curMaxPathSum(m, 0);

    // iterate over each row from row #1 onwards and keep updating the max drop path sum
    for (int i=1; i < n; ++i){
        // compute the max dropping path ending at matrix[i][j]
        for (int j=0; j != m; ++j){
            int best_val = INT_MIN;
            for (int k=0; k != m; ++k){
                int cur_val = maxPathSum[k] + matrix[i][j] - abs(j-k);
                // cout << "\t\ti: " << i << " :: j: " << j << " :: k: " << k << " :: cur_val: " << cur_val << endl;
                best_val = max(best_val, cur_val);
            }
            // cout << "\ti: " << i << " :: j: " << j << " :: best_val: " << best_val << endl;
            curMaxPathSum[j] = best_val;
        }

        // update maxPathSum for i'th row
        maxPathSum = curMaxPathSum;
    }

    return *max_element(maxPathSum.begin(), maxPathSum.end());
}
