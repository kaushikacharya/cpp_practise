// http://www.geeksforgeeks.org/transform-bst-sum-tree/
// Date: Jan 26, 2015

#include <iostream>
#include <queue>
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
    TreeNode<T>* transform_BST(TreeNode<T>* root)
    {
        T sum = sum_tree(root);

        // Now do the inorder traversal
        // And while doing the traversal keep changing the values of the node to greater sum
        stack<TreeNode<T>*> stk;
        TreeNode<T>* node = root;

        while ( (!stk.empty()) || (node) )
        {
            if (node)
            {
                stk.push(node);
                node = node->left;
            }
            else
            {
                node = stk.top();
                stk.pop();
                sum -= node->val;
                node->val = sum;
                node = node->right;
            }
        }

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
    // recursive implementation
    T sum_tree(TreeNode<T>* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        T sum = node->val + sum_tree(node->left) + sum_tree(node->right);
        return sum;
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
    int arr[] = {11, 2, 29, 1, 7, 15, 40, 35};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    BST<int> bst;
    TreeNode<int>* root = bst.create_bst(vec);
    Solution<int> sln;
    TreeNode<int>* transformedBSTRoot = sln.transform_BST(root);
    sln.print_tree_bfs(transformedBSTRoot);

    return 0;
}
