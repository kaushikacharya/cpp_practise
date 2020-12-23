/**
* https://binarysearch.com/problems/Diagonal-Tree-Traversal
* Dec 22, 2020
*/

#include <diagonal_tree_traversal.hpp>

using namespace std;

vector<int> solve(Tree* root) {
    vector<int> diagonalSumVec;

    if (root == nullptr){
        return diagonalSumVec;
    }

    // stack of a) node val  b) diagonal position
    // Algorithm: node and its right child are in same diagonal
    //          left child of node is in the next diagonal of node's diagonal.
    //  Traverse the tree and sum the values for the diagonal position it belongs to.
    stack<pair<Tree*, int> > stk;
    stk.push(make_pair(root, 0));

    while (!stk.empty()){
        pair<Tree*, int> elem = stk.top();
        stk.pop();
        Tree* node = elem.first;
        int diagonal_pos = elem.second;

        if (diagonal_pos == diagonalSumVec.size()){
            diagonalSumVec.push_back(node->val);
        } else if (diagonal_pos < diagonalSumVec.size()) {
            diagonalSumVec[diagonal_pos] += node->val;
        } else {
            assert(false && "diagonal_pos is beyond diagonalSumVec");
        }

        if (node->left){
            stk.push(make_pair(node->left, diagonal_pos+1));
        }

        if (node->right){
            stk.push(make_pair(node->right, diagonal_pos));
        }
    }

    return diagonalSumVec;
}
