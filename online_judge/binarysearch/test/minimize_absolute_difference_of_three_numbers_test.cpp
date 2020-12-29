/**
* https://binarysearch.com/problems/Tree-with-Distinct-Parities
* Dec 27, 2020
*/

#include <minimize_absolute_difference_of_three_numbers.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<int> a = {1, 8, 5};
        vector<int> b = {2, 9};
        vector<int> c = {5, 4};
        EXPECT(solve(a,b,c) == 3);
    }},
    {CASE("Test case: 2"){
        vector<int> a = {1, 8, 5};
        vector<int> b = {12, 9};
        vector<int> c = {5, 4};
        EXPECT(solve(a,b,c) == 5);
    }},
    {CASE("Test case: 3"){
        vector<int> a = {1, 8, 5};
        vector<int> b = {-7, 0};
        vector<int> c = {5, 4};
        EXPECT(solve(a,b,c) == 5);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
