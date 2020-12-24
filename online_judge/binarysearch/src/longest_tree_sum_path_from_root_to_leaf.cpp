/**
* https://binarysearch.com/problems/Longest-Tree-Sum-Path-From-Root-to-Leaf
* Dec 24, 2020
*/

#include <longest_tree_sum_path_from_root_to_leaf.hpp>

using namespace std;

int solve(Tree* root) {
    if (root == nullptr){
        return 0;
    }

    /* Approach: DFS traversal
    *   As we traverse, store the path length from root and the path sum.
    */
    stack<tuple<Tree*, int, int> > stk;  // tuple elements: node, path length, path sum
    stk.push(make_tuple(root, 1, root->val));

    int max_path_length = INT_MIN;
    int max_path_sum = 0; // Path sum corresponding to the path length represented by max_path_length

    while (!stk.empty()){
        tuple<Tree*, int, int> elem = stk.top();
        stk.pop();

        Tree* node = get<0>(elem);
        int path_lenth = get<1>(elem);
        int path_sum = get<2>(elem);

        if ((node->left == nullptr) && (node->right == nullptr)){
            // leaf node
            if (path_lenth > max_path_length){
                max_path_length = path_lenth;
                max_path_sum = path_sum;
            } else if (path_lenth == max_path_length){
                max_path_sum = max(path_sum, max_path_sum);
            }
        } else {
            if (node->right){
                stk.push(make_tuple(node->right, path_lenth+1, path_sum+node->right->val));
            }
            if (node->left){
                stk.push(make_tuple(node->left, path_lenth+1, path_sum+node->left->val));
            }
        }
    }

    return max_path_sum;

}
