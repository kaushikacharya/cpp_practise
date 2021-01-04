/**
* Problem: Recursive Voting
* URL: https://binarysearch.com/problems/Recursive-Voting
* Date: Jan 04, 2021
*/

#include <recursive_voting.hpp>

int solve(vector<int>& votes) {
    int n = votes.size();

    stack<int> stk;
    for (unsigned int i=0; i != n; ++i){
        int j = i;
        // Store the vector positions which have recursive voting starting from i'th position
        while ((votes[j] >= 0) && (votes[j] < n)){
            stk.push(j);
            j = votes[j];
        }
        int val = votes[j];

        // Now replace the recursive voting with the final voting
        while (!stk.empty()){
            j = stk.top();
            stk.pop();
            votes[j] = val;
        }
    }

    int n_votes_a = 0;
    for (vector<int>::iterator it=votes.begin(); it != votes.end(); ++it){
        if (*it < 0){
            ++n_votes_a;
        }
    }

    return n_votes_a;
}

