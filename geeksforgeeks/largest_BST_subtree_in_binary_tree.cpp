// http://www.geeksforgeeks.org/find-the-largest-subtree-in-a-tree-that-is-also-a-bst/
// Date: Jan 26, 2015

#include <iostream>
#include <tuple>
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
    pair<TreeNode<T>*,int> find_largest_BST_subtree(TreeNode<T>* root)
    {
        root_largest_BST_subtree_ = NULL;
        size_largest_BST_subtree_ = 0;

        if (root == NULL)
        {
            return make_pair<TreeNode<T>*,int>(NULL,0);
        }

        is_BST_subtree(root);
        return make_pair(root_largest_BST_subtree_, size_largest_BST_subtree_);
    }
private:
    // ouput tuple: a) is BST (b) min value  (c) max value  (d) size of subtree
    tuple<bool,T,T,int> is_BST_subtree(TreeNode<T>* node)
    {
        // check recursively if the subtree with node as root is BST or not
        bool is_BST = false;
        T min_value_BST;
        T max_value_BST;
        int size_BST;

        if ( (node->left == NULL) && (node->right == NULL) )
        {
            is_BST = true;
            min_value_BST = node->val;
            max_value_BST = node->val;
            size_BST = 1;
        }
        else if (node->right == NULL)
        {
            // only left subtree present
            tuple<bool,T,T,int> leftOutput = is_BST_subtree(node->left);
            bool is_left_BST = get<0>(leftOutput);

            if (is_left_BST)
            {
                T min_left_BST = get<1>(leftOutput);
                T max_left_BST = get<2>(leftOutput);
                int size_left_BST = get<3>(leftOutput);

                if (max_left_BST <= node->val)
                {
                    is_BST = true;
                    min_value_BST = min_left_BST;
                    max_value_BST = node->val;
                    size_BST = size_left_BST + 1;
                }
            }
        }
        else if (node->left == NULL)
        {
            // only right subtree present
            tuple<bool,T,T,int> rightOutput = is_BST_subtree(node->right);
            bool is_right_BST = get<0>(rightOutput);

            if (is_right_BST)
            {
                T min_right_BST = get<1>(rightOutput);
                T max_right_BST = get<2>(rightOutput);
                int size_right_BST = get<3>(rightOutput);

                if (node->val < min_right_BST)
                {
                    is_BST = true;
                    min_value_BST = node->val;
                    max_value_BST = max_right_BST;
                    size_BST = size_right_BST + 1;
                }
            }
        }
        else
        {
            // both subtrees are present
            tuple<bool,T,T,int> leftOutput = is_BST_subtree(node->left);
            tuple<bool,T,T,int> rightOutput = is_BST_subtree(node->right);

            bool is_left_BST = get<0>(leftOutput);
            bool is_right_BST = get<0>(rightOutput);

            if (is_left_BST && is_right_BST)
            {
                T min_left_BST = get<1>(leftOutput);
                T max_left_BST = get<2>(leftOutput);
                int size_left_BST = get<3>(leftOutput);

                T min_right_BST = get<1>(rightOutput);
                T max_right_BST = get<2>(rightOutput);
                int size_right_BST = get<3>(rightOutput);

                if ( (max_left_BST <= node->val) && (node->val < min_right_BST) )
                {
                    is_BST = true;
                    min_value_BST = min_left_BST;
                    max_value_BST = max_right_BST;
                    size_BST = size_left_BST + size_right_BST + 1;
                }
            }
        }

        if (is_BST)
        {
            if (size_largest_BST_subtree_ < size_BST)
            {
                size_largest_BST_subtree_ = size_BST;
                root_largest_BST_subtree_ = node;
            }
        }
        return make_tuple(is_BST, min_value_BST, max_value_BST, size_BST);
    }
private:
    TreeNode<T>* root_largest_BST_subtree_;
    int size_largest_BST_subtree_;
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
    int arr[] = {60, 45, 70, 65, 80};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    BST<int> bst;
    TreeNode<int>* root_bst = bst.create_bst(vec);
    TreeNode<int>* root = new TreeNode<int>(50);
    root->right = root_bst;
    TreeNode<int>* node0 = new TreeNode<int>(30);
    TreeNode<int>* node1 = new TreeNode<int>(5);
    TreeNode<int>* node2 = new TreeNode<int>(20);
    node0->left = node1;
    node0->right = node2;
    root->left = node0;

    Solution<int> sln;
    pair<TreeNode<int>*,int> output = sln.find_largest_BST_subtree(root);
    cout << "root of BST: " << output.first->val << " size of BST: " << output.second << endl;

    return 0;
}
