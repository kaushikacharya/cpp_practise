/**
* https://binarysearch.com/problems/Diagonal-Tree-Traversal
* Dec 22, 2020
*/

#include <diagonal_tree_traversal.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Single node"){
        Tree* root = new Tree;
        root->val = 3;
        root->left = nullptr;
        root->right = nullptr;
        vector<int> diagonalSumVec = {3};
        EXPECT(solve(root) == diagonalSumVec);
    }},
    {CASE("Empty tree"){
        Tree* root = nullptr;
        vector<int> diagonalSumVec = {};
        EXPECT(solve(root) == diagonalSumVec);
    }},
    {CASE("Five nodes tree"){
        Tree* root = new Tree;
        root->val = 1;
        Tree* node_left_root = new Tree;
        node_left_root->val = 4;
        node_left_root->left = nullptr;
        node_left_root->right = nullptr;
        Tree* node_right_root = new Tree;
        node_right_root->val = 2;
        root->left = node_left_root;
        root->right = node_right_root;
        Tree* node_5 = new Tree;
        node_5->val = 5;
        node_5->right = nullptr;
        node_right_root->left = node_5;
        node_right_root->right = nullptr;
        Tree* node_7 = new Tree;
        node_7->val = 7;
        node_7->left = nullptr;
        node_7->right = nullptr;
        node_5->left = node_7;

        vector<int> diagonalSumVec = {3,9,7};
        EXPECT(solve(root) == diagonalSumVec);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}

