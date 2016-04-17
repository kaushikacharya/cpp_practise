// http://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/
// Date: Jan 25, 2015

#include <iostream>
#include <stack>
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
    // k is based on 1-indexed
    TreeNode<T>* kth_smallest_element(TreeNode<T>* root, int k)
    {
        stack<pair<TreeNode<T>*, bool> > stk;
        // bool flag is assigned false for first time when the node is placed in stack
        // Then next time the node and its children are places in stack.
        // That time we assign flag=true. This also means that all the nodes in the left subtree have been explored.

        TreeNode<T>* node = root;
        stk.push(make_pair(node, false));
        int pos = 0;
        TreeNode<T>* kthNode = NULL;

        while (!stk.empty())
        {
            pair<TreeNode<T>*, bool> elem = stk.top();
            stk.pop();

            node = elem.first;
            bool flag = elem.second;

            if (flag)
            {
                ++pos;
                if (pos == k)
                {
                    kthNode = node;
                    break;
                }
            }
            else
            {
                if (node->right)
                {
                    stk.push(make_pair(node->right, false));
                }
                stk.push(make_pair(node, true));
                if (node->left)
                {
                    stk.push(make_pair(node->left, false));
                }
            }
        }

        // empty the stack
        while (!stk.empty())
        {
            stk.pop();
        }

        return kthNode;
    }
};

template <typename T>
class BST
{
    public:
        TreeNode<T>* create_bst(vector<T> vec)
        {
            if (vec.empty())
            {
                return NULL;
            }

            root_ = new TreeNode<T>(vec[0]);
            for (int i = 1; i != vec.size(); ++i)
            {
                TreeNode<T>* node = root_;

                // append the current element in its proper position in the tree
                while (node)
                {
                    if (vec[i] <= node->val)
                    {
                        if (node->left)
                        {
                            node = node->left;
                        }
                        else
                        {
                            TreeNode<T>* newNode = new TreeNode<T>(vec[i]);
                            node->left = newNode;
                            break;
                        }
                    }
                    else
                    {
                        if (node->right)
                        {
                            node = node->right;
                        }
                        else
                        {
                            TreeNode<T>* newNode = new TreeNode<T>(vec[i]);
                            node->right = newNode;
                            break;
                        }
                    }
                }
            }

            return root_;
        }

        TreeNode<T>* root()
        {
            return root_;
        }

    private:
        TreeNode<T>* root_;
};

int main(int argc, char* argv[])
{
    int arr[] = {20, 8, 22, 4, 12, 10, 14};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    BST<int> bst;
    TreeNode<int>* root = bst.create_bst(vec);

    int k = 1;
    Solution<int> sln;
    TreeNode<int>* kthNode = sln.kth_smallest_element(root, k);

    cout << "kth node: " << kthNode->val << endl;

    return 0;
}

/*
Alternate solutions:

Solution #1:
Threaded Binary Tree (mentioned in geeksforgeeks page).
http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/

Solution #2:
Augmented Tree data structure
Maintain number of elements of left subtree in every node.
*/
