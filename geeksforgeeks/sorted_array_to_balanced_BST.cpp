// http://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
// Date: Jan 25, 2015

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
    TreeNode<T>* create_BST(vector<T>& vec)
    {
        if (vec.empty())
        {
            return NULL;
        }

        TreeNode<T>* root = build_subtree_BST(vec, 0, vec.size()-1);
        return root;
    }

    // print tree
    void print_tree_bfs(TreeNode<T>* root)
    {
        queue<TreeNode<T>*> Q;
        Q.push(root);

        while (!Q.empty())
        {
            TreeNode<T>* node = Q.front();
            Q.pop();

            cout << "node: " << node->val;

            if (node->left)
            {
                cout << " left: " << node->left->val;
                Q.push(node->left);
            }
            if (node->right)
            {
                cout << " right: " << node->right->val;
                Q.push(node->right);
            }
            cout << endl;
        }
    }
private:
    // vec[begin_index, .... , end_index]
    TreeNode<T>* build_subtree_BST(vector<T>& vec, int begin_index, int end_index)
    {
        int mid_index = (begin_index+end_index)/2;
        TreeNode<T>* node = new TreeNode<T>(vec[mid_index]);

        if (begin_index == end_index)
        {
            return node;
        }

        if (begin_index < mid_index)
        {
            TreeNode<T>* leftNode = build_subtree_BST(vec, begin_index, mid_index-1);
            node->left = leftNode;
        }
        if (mid_index < end_index)
        {
            TreeNode<T>* rightNode = build_subtree_BST(vec, mid_index+1, end_index);
            node->right = rightNode;
        }

        return node;
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {1,2,3,4,5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution<int> sln;
    TreeNode<int>* root = sln.create_BST(vec);
    sln.print_tree_bfs(root);

    return 0;
}
