/**
* https://binarysearch.io/problems/Kth-Last-Node-of-a-Linked-List
* July 31, 2020
*/

#include<bits/stdc++.h>

using namespace std;

class LLNode {
  public:
    int val;
    LLNode* next;
};

class Solution {
  public:
      int solve(LLNode* node, int k) {
        // Write your code here
        LLNode* pt1 = node;
        LLNode* pt2 = node; // forward pointer

        // move pt2 so that there's k node between it and pt1
        int i=0;
        while (i <= k){
            pt2 = pt2->next;
            ++i;
        }

        // Now move both the pointers together
        while (pt2 != nullptr){
            pt2 = pt2->next;
            pt1 = pt1->next;
            // cout << pt1->val << endl;
        }

        return pt1->val;
  }
};

LLNode* create_linked_list(vector<int> vec){
    if (vec.empty())
    {
        return nullptr;
    }

    LLNode* headNode = new LLNode;
    headNode->val = *(vec.begin());
    headNode->next = nullptr;

    LLNode* prevNode = headNode;

    for (vector<int>::iterator it=vec.begin()+1; it != vec.end(); ++it){
        // cout << "vector element: " << *it << endl;
        LLNode* curNode = new LLNode;
        curNode->val = *it;
        curNode->next = nullptr;

        // assign curNode as next of prevNode
        prevNode->next = curNode;

        // Now set current node as prev node before entering next iteration
        prevNode = curNode;
    }

    return headNode;
}

int main(int argc, char ** argv)
{
    vector<int> vec = {10,20,30,40,50};
    int k = 0;

    LLNode* headNode = create_linked_list(vec);

    Solution sln;
    int kthNodeVal = sln.solve(headNode, k);
    cout << kthNodeVal << endl;
}

/**
* Approach: Two pointers used. Place the pointers such that there are k nodes in between them.
*           Then move both pointers one step at a time. The moment the forward pointer reaches the tail of the linked list,
*           the node being pointed by the other pointer would refer to the solution.
*
* Reference:
*       https://www.geeksforgeeks.org/nth-node-from-the-end-of-a-linked-list/
*       Two approaches mentioned. Apart from double pointer approach, this also provides approach using length of the linked list.
*/
