/**
* Problem: Number of Moves to Capture the King
* URL: https://binarysearch.com/problems/Number-of-Moves-to-Capture-the-King
* Date: Jan 03, 2021
*
*/

#include <number_of_moves_to_capture_the_king.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<vector<int>> board = {{1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 2},
                                    {1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0}};
        EXPECT(solve(board) == 2);
    }},
    {CASE("Test case: 2"){
        vector<vector<int>> board = {{1, 2},
                                    {1, 1}};
        EXPECT(solve(board) == -1);
    }},
    {CASE("Test case: 3"){
        vector<vector<int>> board = {{0, 1, 2},
                                    {0, 1, 0},
                                    {0, 0, 0}};
        EXPECT(solve(board) == 3);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
