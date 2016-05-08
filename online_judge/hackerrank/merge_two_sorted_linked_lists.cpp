// https://www.hackerrank.com/challenges/merge-two-sorted-linked-lists
// May 07, 2016

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* create_linked_list(vector<int>& vec)
{
    if (vec.empty())
    {
        return NULL;
    }

    Node* head = new Node;
    head->data = vec[0];
    head->next = NULL;
    Node* curNode = head;

    for (unsigned int i=1; i != vec.size(); ++i)
    {
        Node* nextNode = new Node;
        nextNode->data = vec[i];
        nextNode->next = NULL;

        curNode->next = nextNode;
        curNode = nextNode;
    }

    return head;
}

void print_linked_list(Node* head)
{
    Node* curNode = head;

    while (curNode)
    {
        cout << curNode->data;
        if (curNode->next)
        {
            cout << ",";
        }
        curNode = curNode->next;
    }
}

void test_linked_list()
{
    vector<int> vec = {1,2,3,4};
    Node* head = create_linked_list(vec);
    cout << "Input linked list: ";
    print_linked_list(head);
    cout << endl;

    Node* curNode = head;
    Node* nextNode = curNode->next;
    curNode->next = nextNode->next;
    cout << "Linked list with head as curNode: ";
    print_linked_list(curNode);
    cout << endl;

    cout << "Linked list with head as head: ";
    print_linked_list(head);
    cout << endl;
}

Node* MergeLists(Node *headA, Node* headB)
{
  // This is a "method-only" submission.
  // You only need to complete this method

  // Handling case when any of the linked list is empty
  if (headA == NULL)
  {
      return headB;
  }
  if (headB == NULL)
  {
      return headA;
  }

  Node* nodeMerged;
  Node* nodeOther;

  // Assign the head of merged list
  Node* headMerged;

  if (headA->data <= headB->data)
  {
      nodeMerged = headA;
      nodeOther = headB;
  }
  else
  {
      nodeMerged = headB;
      nodeOther = headA;
  }
  headMerged = nodeMerged;

  while (nodeMerged->next)
  {
      if (nodeOther->data < nodeMerged->next->data)
      {
          Node* node = nodeMerged->next;
          nodeMerged->next = nodeOther;
          nodeOther = node;
      }
      nodeMerged = nodeMerged->next;
  }
  nodeMerged->next = nodeOther;

  return headMerged;
}

int main(int argc, char* argv[])
{
    // test_linked_list();
    vector<int> vecA = {1,2,6};
    vector<int> vecB = {3,4};
    Node* headA = create_linked_list(vecA);
    Node* headB = create_linked_list(vecB);
    Node* headMerged = MergeLists(headA, headB);
    print_linked_list(headMerged);
    return 0;
}
