/**
* Problem: Tree Shifting
* URL: https://binarysearch.com/problems/Tree-Shifting
* Date: Feb 01,2021
*
* Algorithm:
*   Time Complexity: O(n)
*   Space Complexity: O(n)
*
*   Maintain two queues:
*       One for the level whose children you want to shift.
*       Second one contains the children.
*   Keep the nodes in the queue in the order of right to left.
*   As we go from root level to the lowest leaf level, keep shifting the children so that they are as right as possible.
*/

#include <tree_shifting.hpp>

Tree* solve(Tree* root) {
    if (root == nullptr){
        return root;
    }

    // Elements at any particular level are pushed into queue in right to left direction.
    queue<Tree*> nextIterQ;
    nextIterQ.push(root);

    // In each iteration, shift the child nodes of the current level
    while (!nextIterQ.empty()){
        // cout << "\nIteration: " << endl;
        unsigned int n_nextIterQ = nextIterQ.size();
        queue<Tree*> curLevelQ = nextIterQ;
        // Populate child nodes in the queue so that this queue is assigned to nextIterQ for the next iteration.
        queue<Tree*> childLevelQ;

        while (!nextIterQ.empty()){
            Tree* curNode = nextIterQ.front();
            // cout << "\tcurNode: " << curNode->val << endl;
            nextIterQ.pop();
            // cout << "\t(After pop): curNode: " << curNode->val << endl;

            if (curNode->right){
                childLevelQ.push(curNode->right);
            }
            if (curNode->left){
                childLevelQ.push(curNode->left);
            }
        }

        // cout << "\tNumber of elements in childLevelQ: " << childLevelQ.size() << endl;

        assert(n_nextIterQ == curLevelQ.size() && "queue assignment wasn't copy by value");

        // save the child level queue for next iteration
        nextIterQ = childLevelQ;

        // For every element of curLevelQ take two elements of childLevelQ (if available) and assign as its right and left child.
        while (!curLevelQ.empty()){
            Tree* curNode = curLevelQ.front();
            curLevelQ.pop();

            Tree* rightChildNode = nullptr;
            Tree* leftChildNode = nullptr;

            if (!childLevelQ.empty()){
                rightChildNode = childLevelQ.front();
                childLevelQ.pop();
            }

            if (!childLevelQ.empty()){
                leftChildNode = childLevelQ.front();
                childLevelQ.pop();
            }

            curNode->right = rightChildNode;
            curNode->left = leftChildNode;
        }
    }

    return root;
}
