// http://www.geeksforgeeks.org/bottom-view-binary-tree/
// http://cs.stackexchange.com/questions/22801/print-bottom-view-of-a-binary-tree (nice explanation of the problem)
// Date: Feb 16, 2015

#include <iostream>
#include <queue>
#include <map>

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
    void bottom_view_of_binary_tree(TreeNode<T>* root)
    {
        typedef map<int,TreeNode<T>* > Map;
        Map horz_dist_map;
        queue<pair<TreeNode<T>*,int> > Q;
        Q.push(make_pair(root,0));
        horz_dist_map.insert(make_pair(0,root));

        while (!Q.empty())
        {
            pair<TreeNode<T>*,int> elem = Q.front();
            Q.pop();
            TreeNode<T>* node = elem.first;
            int horizontal_distance = elem.second;

            if (node->left)
            {
                Q.push(make_pair(node->left, horizontal_distance-1));
                typename Map::iterator it = horz_dist_map.find(horizontal_distance-1);

                if (it == horz_dist_map.end())
                {
                    horz_dist_map.insert(make_pair(horizontal_distance-1,node->left));
                }
                else
                {
                    (*it).second = node->left;
                }
            }
            if (node->right)
            {
                Q.push(make_pair(node->right, horizontal_distance+1));
                typename Map::iterator it = horz_dist_map.find(horizontal_distance+1);

                if (it == horz_dist_map.end())
                {
                    horz_dist_map.insert(make_pair(horizontal_distance+1,node->right));
                }
                else
                {
                    (*it).second = node->right;
                }
            }
        }

        // Now print the bottom view
        for (typename Map::iterator it = horz_dist_map.begin(); it != horz_dist_map.end(); ++it)
        {
            if (it != horz_dist_map.begin())
            {
                cout << " ";
            }
            cout << (*it).second->val;
        }
    }
};


int main(int argc, char* argv[])
{
    TreeNode<int>* root = new TreeNode<int>(20);
    root->left = new TreeNode<int>(8);
    root->right = new TreeNode<int>(22);
    root->right->left = new TreeNode<int>(4);
    root->right->right = new TreeNode<int>(25);
    root->left->left = new TreeNode<int>(5);
    root->left->right = new TreeNode<int>(3);
    root->left->right->left = new TreeNode<int>(10);
    root->left->right->right = new TreeNode<int>(14);

    Solution<int> sln;
    sln.bottom_view_of_binary_tree(root);

    return 0;
}

/*
http://stackoverflow.com/questions/2795023/c-template-typedef
*/
