/**
* https://binarysearch.com/problems/Increasing-Subsequences-of-Size-K
* Dec 25, 2020
*/

#include <increasing_subsequences_of_size_k.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("[1,2,3,0] k=2"){
        vector<int> nums{1,2,3,0};
        int k = 2;
        EXPECT(solve(nums, k) == 3);
    }},
    {CASE("[1,2,2,0] k=2"){
        vector<int> nums{1,2,2,0};
        int k = 2;
        EXPECT(solve(nums, k) == 2);
    }},
    {CASE("[1,2,3,4,0,0] k=3"){
        vector<int> nums{1,2,3,4,0,0};
        int k = 3;
        EXPECT(solve(nums, k) == 4);
    }},
    {CASE("[1,2,3,0] k=4"){
        vector<int> nums{1,2,3,0};
        int k = 4;
        EXPECT(solve(nums, k) == 0);
    }},
    {CASE("[0,....,499] k=10"){
        vector<int> nums(500);
        // https://en.cppreference.com/w/cpp/algorithm/iota
        iota(nums.begin(), nums.end(), 0);
        int k = 10;
        EXPECT(solve(nums, k) == 216989133);
    }},
    {CASE("[0,....,7] k=4"){
        vector<int> nums(8);
        iota(nums.begin(), nums.end(), 0);
        int k = 4;
        EXPECT(solve(nums, k) == 70);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
