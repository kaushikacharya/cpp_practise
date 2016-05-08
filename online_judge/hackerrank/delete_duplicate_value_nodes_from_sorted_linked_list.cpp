// https://www.hackerrank.com/challenges/delete-duplicate-value-nodes-from-a-sorted-linked-list
// May 08, 2016

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

Node* RemoveDuplicates(Node *head)
{
  // This is a "method-only" submission.
  // You only need to complete this method.
  Node* node = head;
  while (node && node->next)
  {
      if (node->data == node->next->data)
      {
          Node* nextNode = node->next;
          while (nextNode && nextNode->data == node->data)
          {
              nextNode = nextNode->next;
          }
          node->next = nextNode;
      }
      node = node->next;
  }

  return head;
}


int main(int argc, char* argv[])
{
    vector<int> vec = {};
    Node* head = create_linked_list(vec);
    cout << "Input linked list: ";
    print_linked_list(head);
    cout << endl;

    head = RemoveDuplicates(head);
    cout << "Linked list(post deduplication): ";
    print_linked_list(head);
    cout << endl;

    return 0;
}
