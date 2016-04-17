// http://www.geeksforgeeks.org/given-binary-tree-print-nodes-two-given-level-numbers/
// Date: Jan 15, 2015

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
        // Notation: root's level = 1
        void print_nodes(TreeNode<T>* root, int st_level, int end_level)
        {
            queue<TreeNode<T>*> Q;
            Q.push(root);
            int nElemInLevel = 1;
            bool flagFirstElemOfLevel = true;
            int level = 1;

            while (!Q.empty())
            {
                TreeNode<T>* elem = Q.front();
                Q.pop();
                // push its children into queue
                if (elem->left)
                {
                    Q.push(elem->left);
                }
                if (elem->right)
                {
                    Q.push(elem->right);
                }

                --nElemInLevel;

                // print only the nodes in level [st_level,...,end_level]
                if (level >= st_level)
                {
                    if (!flagFirstElemOfLevel)
                    {
                        cout << " ";
                    }
                    cout << elem->val;
                }

                if (nElemInLevel == 0)
                {
                    // rightmost element of level has been processed
                    if (level >= st_level)
                    {
                        cout << endl;
                    }
                    ++level;
                    nElemInLevel = Q.size();
                    flagFirstElemOfLevel = true;
                }
                else
                {
                    flagFirstElemOfLevel = false;
                }

                if (level > end_level)
                {
                    break;
                }
            }

            // empty the queue
            while (!Q.empty())
            {
                Q.pop();
            }
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
    bst.create_bst(vec);

    int st_level = 2;
    int end_level = 4;
    Solution<int> sln;
    sln.print_nodes(bst.root(), st_level, end_level);

    return 0;
}
