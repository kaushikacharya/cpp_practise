/**
* https://binarysearch.com/problems/Tree-with-Distinct-Parities
* Dec 27, 2020
*/

#include <tree_with_distinct_parities.hpp>

using namespace std;

int solve(Tree* root) {
    if (root == nullptr){
        return 0;
    }

    pair<int, int> result = compute_parities(root);
    return result.second;
}

pair<int, int> compute_parities(Tree* node){
    int sum_subtree = node->val;
    int count_perfect_nodes = 0;

    pair<int, int> left_result;
    pair<int, int> right_result;

    // Compute parities for left subtree
    if (node->left){
        left_result = compute_parities(node->left);
        sum_subtree += left_result.first;
        count_perfect_nodes += left_result.second;
    }

    // Compute parities for right subtree
    if (node->right){
        right_result = compute_parities(node->right);
        sum_subtree += right_result.first;
        count_perfect_nodes += right_result.second;
    }

    // check if the input subtree's root is a perfect node or not
    if ((node->left) && (node->right)){
        if (((left_result.first % 2 == 0) && (right_result.first % 2 == 1)) || ((left_result.first % 2 == 1) && (right_result.first % 2 == 0))){
            count_perfect_nodes += 1;
        }
    }

    return make_pair(sum_subtree, count_perfect_nodes);
}
