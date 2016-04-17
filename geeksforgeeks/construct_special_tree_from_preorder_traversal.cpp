// http://www.geeksforgeeks.org/construct-a-special-tree-from-given-preorder-traversal/
// Date: Jan 21, 2015

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
    TreeNode(T x): val(x), left(NULL), right(NULL){}
};

template <typename T>
class Solution
{
public:
    TreeNode<T>* create_binary_tree(vector<T>& vecPre, vector<char>& vecPreLN)
    {
        if (vecPre.empty())
        {
            return NULL;
        }

        // store the input vectors
        vecPre_ = vecPre;
        vecPreLN_ = vecPreLN;

        pair<TreeNode<T>*,int> outputPair = range_vec_sub_tree(0, vecPre.size()-1);
        TreeNode<T>* root = outputPair.first;
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
    //input: [b_index, ...., e_index]
    //output: pair of (a) root node of subtree, (b) end index of vecPre_ which is rightmost node of subtree
    pair<TreeNode<T>*,int> range_vec_sub_tree(int b_index, int e_index)
    {
        TreeNode<T>* node = new TreeNode<T>(vecPre_[b_index]);

        if (vecPreLN_[b_index] == 'L')
        {
            return make_pair(node,b_index);
        }

        // assumption: either a node is leaf or has both the children
        pair<TreeNode<T>*,int> leftPair = range_vec_sub_tree(b_index+1, e_index);
        TreeNode<T>* leftChild = leftPair.first;
        int mid_index = leftPair.second;
        pair<TreeNode<T>*,int> rightPair = range_vec_sub_tree(mid_index+1, e_index);
        TreeNode<T>* rightChild = rightPair.first;
        int end_index = rightPair.second;

        node->left = leftChild;
        node->right = rightChild;

        return make_pair(node, end_index);
    }
private:
    vector<T> vecPre_;
    vector<char> vecPreLN_;
};

int main(int argc, char*argv[])
{
    //int preArr[] = {10, 30, 20, 5, 15};
    //char preLNArr[] = {'N', 'N', 'L', 'L', 'L'};
    int preArr[] = {10, 30, 15, 20, 5};
    char preLNArr[] = {'N', 'L', 'N', 'L', 'L'};
    vector<int> preVec(preArr, preArr+sizeof(preArr)/sizeof(preArr[0]));
    vector<char> preLNVec(preLNArr, preLNArr+sizeof(preLNArr)/sizeof(preLNArr[0]));

    Solution<int> sln;
    TreeNode<int>* root = sln.create_binary_tree(preVec, preLNVec);
    sln.print_tree_bfs(root);

    return 0;
}
