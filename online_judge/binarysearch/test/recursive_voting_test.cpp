/**
* Problem: Recursive Voting
* URL: https://binarysearch.com/problems/Recursive-Voting
* Date: Jan 04, 2021
*/

#include <recursive_voting.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case: 1"){
        vector<int> votes = {2, -1, 5, 1, 3};
        EXPECT(solve(votes) == 3);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
