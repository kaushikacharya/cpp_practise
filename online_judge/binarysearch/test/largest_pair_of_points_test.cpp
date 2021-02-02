/**
* Problem: Largest Pair of Points
* URL: https://binarysearch.com/problems/Largest-Pair-of-Points
* Date: Jan 31,2021
*
*/

#include <largest_pair_of_points.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<int> nums = {0, 1, 6};
        vector<int> values = {-5, 5, 4};
        EXPECT(solve(nums, values) == 14);
    }},
    {CASE("Test case: 2"){
        vector<int> nums = {0, 3, 6};
        vector<int> values = {-5, 4, 8};
        EXPECT(solve(nums, values) == 16);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
