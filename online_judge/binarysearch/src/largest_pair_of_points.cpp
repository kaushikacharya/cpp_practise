/**
* Problem: Largest Pair of Points
* URL: https://binarysearch.com/problems/Largest-Pair-of-Points
* Date: Jan 31,2020
*
* Time Complexity: O(n)
* Space Complexity: O(n)
*/

#include <largest_pair_of_points.hpp>

int solve(vector<int>& nums, vector<int>& values) {
    int j = 0;
    int max_value_overall = INT_MIN;
    int max_value_for_ith_pos = INT_MIN;  // values[i] - nums[i]

    /* There are two components:
    *   a) values[i] - nums[i]
    *   b) values[j] + nums[j]
    *   where i <= j
    *
    *   As we progress from 0 to (n-1)'th position,
    *   i) keep track of the max value of component (a).
    *   ii) Check if (max value of component (a) till now) + (current value of component (b)) is higher than till now.
    *
    */
    while (j < nums.size()) {
        int cur_value_for_ith_pos = values[j] - nums[j];
        max_value_for_ith_pos = max(max_value_for_ith_pos, cur_value_for_ith_pos);
        int cur_value_overall = values[j] + nums[j] + max_value_for_ith_pos;
        max_value_overall = max(max_value_overall, cur_value_overall);
        ++j;
    }

    return max_value_overall;
}
