/**
* https://binarysearch.com/problems/Longest-Tree-Sum-Path-From-Root-to-Leaf
* Dec 24, 2020
*/

#include <longest_tree_sum_path_from_root_to_leaf.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Single node"){
        Tree* root = new Tree;
        root->val = 1;
        root->left = nullptr;
        root->right = nullptr;
        int longest_sum_path = 1;
        EXPECT(solve(root) == longest_sum_path);
    }},
    {CASE("null tree"){
        Tree* root = nullptr;;
        int longest_sum_path = 0;
        EXPECT(solve(root) == longest_sum_path);
    }},
    {CASE("Five nodes"){
        Tree* root = new Tree;
        root->val = 1;

        Tree* node_left_root = new Tree;
        node_left_root->val = 5;
        node_left_root->left = nullptr;
        node_left_root->right = nullptr;

        root->left = node_left_root;

        Tree* node_8 = new Tree;
        node_8->val = 8;
        node_8->left = nullptr;
        node_8->right = nullptr;

        Tree* node_7 = new Tree;
        node_7->val = 7;
        node_7->left = nullptr;
        node_7->right = node_8;

        Tree* node_right_root = new Tree;
        node_right_root->val = 4;
        node_right_root->left = node_7;
        node_right_root->right = nullptr;

        root->right = node_right_root;

        int longest_sum_path = 20;
        EXPECT(solve(root) == longest_sum_path);
    }},
    {CASE("Shorter path with larger sum"){
        // Should avoid picking the shorter path having larger sum
        Tree* root = new Tree;
        root->val = 1;

        Tree* node_left_root = new Tree;
        node_left_root->val = 5;
        node_left_root->left = nullptr;
        node_left_root->right = nullptr;

        root->left = node_left_root;

        Tree* node_8 = new Tree;
        node_8->val = 8;
        node_8->left = nullptr;
        node_8->right = nullptr;

        Tree* node_7 = new Tree;
        node_7->val = 7;
        node_7->left = nullptr;
        node_7->right = node_8;

        Tree* node_16 = new Tree;
        node_16->val = 16;
        node_16->left = nullptr;
        node_16->right = nullptr;

        Tree* node_right_root = new Tree;
        node_right_root->val = 4;
        node_right_root->left = node_7;
        node_right_root->right = node_16;

        root->right = node_right_root;

        int longest_sum_path = 20;
        EXPECT(solve(root) == longest_sum_path);
    }}
};


int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
