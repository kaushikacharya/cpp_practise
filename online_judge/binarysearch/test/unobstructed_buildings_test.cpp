/**
* Problem: Unobstructed Buildings
* URL: https://binarysearch.com/problems/Unobstructed-Buildings
* Date: Jan 03, 2021
*
*/

#include <unobstructed_buildings.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<int> heights = {1, 5, 5, 2, 3};
        vector<int> unobstructedIndexVec = {2, 4};
        EXPECT(solve(heights) == unobstructedIndexVec);
    }},
    {CASE("Test case: 2"){
        vector<int> heights = {5, 4, 3, 2, 1};
        vector<int> unobstructedIndexVec = {0, 1, 2, 3, 4};
        EXPECT(solve(heights) == unobstructedIndexVec);
    }},
    {CASE("Test case: 3"){
        vector<int> heights = {1, 1, 1, 1, 1};
        vector<int> unobstructedIndexVec = {4};
        EXPECT(solve(heights) == unobstructedIndexVec);
    }},
    {CASE("Test case: 3"){
        vector<int> heights = {};
        vector<int> unobstructedIndexVec = {};
        EXPECT(solve(heights) == unobstructedIndexVec);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
