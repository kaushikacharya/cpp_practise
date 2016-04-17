// http://www.geeksforgeeks.org/print-ancestors-of-a-given-binary-tree-node-without-recursion/
// Date: Jan 02, 2015

#include <iostream>
#include <stack>

using namespace std;

template <typename T>
struct TreeNode
{
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T x): val(x), left(NULL), right(NULL){}
};


template <typename T>
class Solution
{
    public:
        // Here we do pre-order traversal
        void print_ancestors_of_tree_node_preorder(TreeNode<T>* root, T node_val)
        {
            root_ = root;
            stack<pair<TreeNode<T>*,int> > stk_node_level;
            stack<TreeNode<T>* > stk_ancestors;

            stk_node_level.push(make_pair(root_,0));

            while (!stk_node_level.empty())
            {
                pair<TreeNode<T>*,int> cur_node_level = stk_node_level.top();
                stk_node_level.pop();
                TreeNode<T>* cur_node = cur_node_level.first;
                int cur_level = cur_node_level.second;

                // Ensure that only cur_level number of nodes present in stk_ancestors before push
                while (stk_ancestors.size() > cur_level)
                {
                    stk_ancestors.pop();
                }

                if (cur_node->val == node_val)
                {
                    break;
                }

                // push cur_node in stk_ancestors
                stk_ancestors.push(cur_node);

                if (cur_node->right)
                {
                    stk_node_level.push(make_pair(cur_node->right, cur_level+1));
                }
                if (cur_node->left)
                {
                    stk_node_level.push(make_pair(cur_node->left, cur_level+1));
                }
            }

            // Now print the ancestors
            cout << "ancestors: ";
            while (!stk_ancestors.empty())
            {
                TreeNode<T>* cur_node = stk_ancestors.top();
                stk_ancestors.pop();
                cout << cur_node->val << " ";
            }
        }
    private:
        TreeNode<T>* root_;
};

template <typename T>
TreeNode<T>* create_tree()
{
    /*
            1
        /       \
       2         3
     /   \     /   \
    4     5    6    7
   /       \       /
  8         9     10
    */
    TreeNode<T>* rootNode = new TreeNode<int>(1);
    TreeNode<T>* level1Node0 = new TreeNode<int>(2);
    TreeNode<T>* level1Node1 = new TreeNode<int>(3);
    rootNode->left = level1Node0;
    rootNode->right = level1Node1;
    TreeNode<T>* level2Node0 = new TreeNode<int>(4);
    TreeNode<T>* level2Node1 = new TreeNode<int>(5);
    level1Node0->left = level2Node0;
    level1Node0->right = level2Node1;
    TreeNode<T>* level2Node2 = new TreeNode<int>(6);
    TreeNode<T>* level2Node3 = new TreeNode<int>(7);
    level1Node1->left = level2Node2;
    level1Node1->right = level2Node3;

    TreeNode<T>* level3Node0 = new TreeNode<int>(8);
    TreeNode<T>* level3Node3 = new TreeNode<int>(9);
    level2Node0->left = level3Node0;
    level2Node1->right = level3Node3;

    TreeNode<T>* level3Node6 = new TreeNode<int>(10);
    level2Node3->left = level3Node6;

    return rootNode;
}

int main(int argc, char* argv[])
{
    TreeNode<int>* root = create_tree<int>();
    Solution<int> sln;
    sln.print_ancestors_of_tree_node_preorder(root,2);
    return 0;
}

/*
Check: post-order traversal approach as mentioned in geeksforgeeks
*/
