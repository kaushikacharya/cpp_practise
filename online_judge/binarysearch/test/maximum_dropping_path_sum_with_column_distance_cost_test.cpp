/**
* Problem: Maximum Dropping Path Sum With Column Distance Cost
* URL: https://binarysearch.com/problems/Maximum-Dropping-Path-Sum-With-Column-Distance-Cost
* Date: Jan 04, 2021
*
*/

#include <maximum_dropping_path_sum_with_column_distance_cost.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<vector<int>> matrix = {{3, 2, 1, 6},
                                     {4, 1, 2, 0},
                                     {1, 5, 2, -2}};
        EXPECT(solve(matrix) == 11);
    }},
    {CASE("Test case: 2"){
        vector<vector<int>> matrix = {{3, 2, 1, 7},
                                     {4, 1, 2, 0},
                                     {1, 5, 2, -2}};
        EXPECT(solve(matrix) == 12);
    }},
    {CASE("Test case: 3"){
        vector<vector<int>> matrix = {{7, 6, 5, 6},
                                     {6, 4, 5, 8}};
        EXPECT(solve(matrix) == 14);
    }},
    {CASE("Test case: 4"){
        vector<vector<int>> matrix = {{2, 1, 3}};
        EXPECT(solve(matrix) == 3);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
