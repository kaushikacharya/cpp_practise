/**
* https://binarysearch.com/problems/Tree-with-Distinct-Parities
* Dec 27, 2020
*/

#include <tree_with_distinct_parities.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Five nodes: 2 Perfect nodes"){
        Tree* root = new Tree;
        root->val = 1;

        Tree* node_left_root = new Tree;
        node_left_root->val = 5;
        node_left_root->left = nullptr;
        node_left_root->right = nullptr;

        root->left = node_left_root;

        Tree* node_4 = new Tree;
        node_4->val = 4;
        node_4->left = nullptr;
        node_4->right = nullptr;

        Tree* node_7 = new Tree;
        node_7->val = 7;
        node_7->left = nullptr;
        node_7->right = nullptr;

        Tree* node_right_root = new Tree;
        node_right_root->val = 3;
        node_right_root->left = node_4;
        node_right_root->right = node_7;

        root->right = node_right_root;

        EXPECT(solve(root) == 2);
    }},
    {CASE("Five nodes: 1 Perfect node"){
        Tree* root = new Tree;
        root->val = 1;

        Tree* node_left_root = new Tree;
        node_left_root->val = 5;
        node_left_root->left = nullptr;
        node_left_root->right = nullptr;

        root->left = node_left_root;

        Tree* node_4 = new Tree;
        node_4->val = 4;
        node_4->left = nullptr;
        node_4->right = nullptr;

        Tree* node_8 = new Tree;
        node_8->val = 8;
        node_8->left = nullptr;
        node_8->right = nullptr;

        Tree* node_right_root = new Tree;
        node_right_root->val = 6;
        node_right_root->left = node_4;
        node_right_root->right = node_8;

        root->right = node_right_root;

        EXPECT(solve(root) == 1);
    }},
    {CASE("Three nodes: 1 Perfect node"){
        Tree* root = new Tree;
        root->val = 1;
        root->right = nullptr;

        Tree* node_left_root = new Tree;
        node_left_root->val = 2;
        node_left_root->right = nullptr;

        Tree* node_3 = new Tree;
        node_3->val = 3;
        node_3->left = nullptr;
        node_3->right = nullptr;

        node_left_root->left = node_3;

        root->left = node_left_root;

        EXPECT(solve(root) == 0);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
