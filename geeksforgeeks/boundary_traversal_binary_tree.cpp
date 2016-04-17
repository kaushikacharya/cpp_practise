// http://www.geeksforgeeks.org/boundary-traversal-of-binary-tree/
// Date: Jan 04, 2015

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
struct TreeNode
{
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {};
};

template <typename T>
class Solution
{
public:
    vector<TreeNode<T>* > boundary_traversal(TreeNode<T>* root)
    {
        vector<TreeNode<T>* > vec;

        if (root == NULL)
        {
            return vec;
        }

        root_ = root;

        vector<TreeNode<T>* > vec_left_boundary = left_boundary(root);
        vector<TreeNode<T>* > vec_right_boundary = right_boundary(root);
        vector<TreeNode<T>* > vec_leaf = leaf_nodes_subtree(root);

        vec = vec_left_boundary;
        int i = 0;
        if (vec_left_boundary.back() == vec_leaf.front())
        {
            ++i;
        }
        for (; i < vec_leaf.size(); ++i)
        {
            vec.push_back(vec_leaf[i]);
        }

        i = 0;
        if (vec_leaf.back() == vec_right_boundary.front())
        {
            ++i;
        }
        for (; i < vec_right_boundary.size()-1; ++i)
        {
            vec.push_back(vec_right_boundary[i]);
        }

        return vec;
    }
private:
    vector<TreeNode<T>* > leaf_nodes_subtree(TreeNode<T>* node)
    {
        vector<TreeNode<T>* > vec;
        if ((node->left == NULL) && (node->right == NULL))
        {
            vec.push_back(node); // leaf node
        }
        if (node->left)
        {
            vector<TreeNode<T>* > vec_left_leaf = leaf_nodes_subtree(node->left);
            for (typename vector<TreeNode<T>* >::iterator it = vec_left_leaf.begin(); it != vec_left_leaf.end(); ++it)
            {
                vec.push_back(*it);
            }
        }
        if (node->right)
        {
            vector<TreeNode<T>* > vec_right_leaf = leaf_nodes_subtree(node->right);
            for (typename vector<TreeNode<T>* >::iterator it = vec_right_leaf.begin(); it != vec_right_leaf.end(); ++it)
            {
                vec.push_back(*it);
            }
        }

        return vec;
    }

    vector<TreeNode<T>* > left_boundary(TreeNode<T>* node)
    {
        vector<TreeNode<T>* > vec;

        while (node)
        {
            vec.push_back(node);
            node = node->left;
        }

        return vec;
    }

    // bottom-top order
    vector<TreeNode<T>* > right_boundary(TreeNode<T>* node)
    {
        vector<TreeNode<T>* > vec;
        stack<TreeNode<T>* > stk;

        while (node)
        {
            stk.push(node);
            node = node->right;
        }

        while (!stk.empty())
        {
            TreeNode<T>* curNode = stk.top();
            stk.pop();
            vec.push_back(curNode);
        }

        return vec;
    }
private:
    TreeNode<T>* root_;
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

    private:
        TreeNode<T>* root_;
};

int main(int argc, char* argv[])
{
    /*
    int arr1[] = {9,2,3};
    vector<int> vec1(arr1, arr1+sizeof(arr1)/sizeof(arr1[0]));
    int arr2[] = {3,4};
    vector<int> vec2(arr2, arr2+sizeof(arr2)/sizeof(arr2[0]));
    // error: No operator+
    vector<int> vec3 = vec1+vec2;
    */

    //int arr[] = {20,8,4,12,10,14,22,25};
    int arr[] = {20};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    BST<int> bst;
    TreeNode<int>* root = bst.create_bst(vec);

    Solution<int> sln;
    vector<TreeNode<int>* > vec_boundary = sln.boundary_traversal(root);

    for (vector<TreeNode<int>* >::iterator it = vec_boundary.begin(); it != vec_boundary.end(); ++it)
    {
        cout << (*it)->val << " ";
    }

    return 0;
}
