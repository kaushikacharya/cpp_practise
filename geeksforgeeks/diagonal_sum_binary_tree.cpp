// http://www.geeksforgeeks.org/diagonal-sum-binary-tree/
// Date: Feb 17, 2015

#include <iostream>
#include <queue>
#include <vector>

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
    vector<T> compute_diagonal_sum(TreeNode<T>* root)
    {
        vector<T> vec_diagonal_sum;
        // elem of queue: 1. node  2. diagonal level
        queue<pair<TreeNode<T>*,int> > Q;
        Q.push(make_pair(root,0));

        while (!Q.empty())
        {
            pair<TreeNode<T>*,int> elem = Q.front();
            Q.pop();
            TreeNode<T>* node = elem.first;
            int diagonal_level = elem.second;

            if (vec_diagonal_sum.size() < (diagonal_level+1))
            {
                vec_diagonal_sum.push_back(node->val);
            }
            else
            {
                vec_diagonal_sum[diagonal_level] += node->val;
            }

            if (node->left)
            {
                Q.push(make_pair(node->left, diagonal_level+1));
            }
            if (node->right)
            {
                Q.push(make_pair(node->right, diagonal_level));
            }
        }

        return vec_diagonal_sum;
    }
};

int main(int argc, char* argv[])
{
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(9);
    root->left->right = new TreeNode<int>(6);
    root->left->left->right = new TreeNode<int>(10);
    root->left->right->left = new TreeNode<int>(11);
    root->right->left = new TreeNode<int>(4);
    root->right->right = new TreeNode<int>(5);
    root->right->left->left = new TreeNode<int>(12);
    root->right->left->right = new TreeNode<int>(7);

    Solution<int> sln;
    vector<int> vec_diag_sum = sln.compute_diagonal_sum(root);

    for (vector<int>::iterator it = vec_diag_sum.begin(); it != vec_diag_sum.end(); ++it)
    {
        if (it != vec_diag_sum.begin())
        {
            cout << ",";
        }
        cout << *it;
    }

    return 0;
}
