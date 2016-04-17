// http://www.geeksforgeeks.org/diameter-of-a-binary-tree/
// Date: Feb 15, 2015

#include <iostream>

using namespace std;

template <typename T>
struct TreeNode
{
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(T x): val(x), left(NULL), right(NULL) {}
};

template <typename T>
class Solution
{
public:
    int compute_diameter_of_binary_tree(TreeNode<T>* root)
    {
        diameter_ = 0;

        if (root)
        {
            compute_max_length_to_leaf(root);
        }

        return diameter_;
    }
private:
    // by length we mean number of nodes from node to leaf
    int compute_max_length_to_leaf(TreeNode<T>* node)
    {
        int left_subtree_max_length_to_leaf = 0;
        if (node->left)
        {
            left_subtree_max_length_to_leaf = compute_max_length_to_leaf(node->left);
        }
        int right_subtree_max_length_to_leaf = 0;
        if (node->right)
        {
            right_subtree_max_length_to_leaf = compute_max_length_to_leaf(node->right);
        }

        int diameter_of_subtree = left_subtree_max_length_to_leaf + right_subtree_max_length_to_leaf + 1;
        if (diameter_ < diameter_of_subtree)
        {
            diameter_ = diameter_of_subtree;
        }

        int max_length_to_leaf = (left_subtree_max_length_to_leaf < right_subtree_max_length_to_leaf) ?
                (right_subtree_max_length_to_leaf+1) : (left_subtree_max_length_to_leaf+1);
        return max_length_to_leaf;
    }
private:
    int diameter_;
};

int main(int argc, char* argv[])
{
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(4);
    root->left->left->left = new TreeNode<int>(10);
    root->left->right = new TreeNode<int>(5);
    root->left->right->left = new TreeNode<int>(6);
    root->left->right->right = new TreeNode<int>(7);
    root->left->right->right->right = new TreeNode<int>(8);


    Solution<int> sln;
    int diameter = sln.compute_diameter_of_binary_tree(root);
    cout << diameter << endl;

    return 0;
}
