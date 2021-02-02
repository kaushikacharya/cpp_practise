/**
* Problem: Tree Shifting
* URL: https://binarysearch.com/problems/Tree-Shifting
* Date: Feb 01,2021
*/

#include <tree_shifting.hpp>
#include <lest.hpp>

const lest::test tests[] = {
    {CASE("Test case 1"){
        Tree* node_4 = new Tree;
        node_4->val = 4;
        node_4->left = nullptr;
        node_4->right = nullptr;

        Tree* node_2 = new Tree;
        node_2->val = 2;
        node_2->left = node_4;
        node_2->right = nullptr;

        Tree* node_6 = new Tree;
        node_6->val = 6;
        node_6->left = nullptr;
        node_6->right = nullptr;

        Tree* node_7 = new Tree;
        node_7->val = 7;
        node_7->left = nullptr;
        node_7->right = nullptr;

        Tree* node_5 = new Tree;
        node_5->val = 5;
        node_5->left = node_6;
        node_5->right = node_7;

        Tree* node_3 = new Tree;
        node_3->val = 3;
        node_3->left = node_5;
        node_3->right = nullptr;

        Tree* root = new Tree;
        root->val = 1;
        root->left = node_2;
        root->right = node_3;

        Tree* shifted_tree_root = solve(root);
        EXPECT(shifted_tree_root->left->val == 2);
        EXPECT(shifted_tree_root->left->left == nullptr);
        EXPECT(shifted_tree_root->left->right == nullptr);
        EXPECT(shifted_tree_root->right->val == 3);
        EXPECT(shifted_tree_root->right->left->val == 4);
        EXPECT(shifted_tree_root->right->left->left == nullptr);
        EXPECT(shifted_tree_root->right->left->right == nullptr);
        EXPECT(shifted_tree_root->right->right->val == 5);
    }},
    {CASE("Test case 2"){
        Tree* root = new Tree;
        root->val = 1;
        root->left = nullptr;
        root->right = nullptr;

        Tree* shifted_tree_root = solve(root);
        EXPECT(shifted_tree_root->left == nullptr);
        EXPECT(shifted_tree_root->right == nullptr);
    }},
    {CASE("Test case 3"){
        Tree* node_2 = new Tree;
        node_2->val = 2;
        node_2->left = nullptr;
        node_2->right = nullptr;

        Tree* root = new Tree;
        root->val = 1;
        root->left = node_2;
        root->right = nullptr;

        Tree* shifted_tree_root = solve(root);
        EXPECT(shifted_tree_root->left == nullptr);
        EXPECT(shifted_tree_root->right->val == 2);
        EXPECT(shifted_tree_root->right->left == nullptr);
        EXPECT(shifted_tree_root->right->right == nullptr);
    }},
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
