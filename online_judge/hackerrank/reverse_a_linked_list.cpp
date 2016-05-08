// https://www.hackerrank.com/challenges/reverse-a-linked-list
// May 07, 2016

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    struct Node* next;
};

Node* Reverse(Node *head)
{
  Node* prevNode = NULL;
  Node* curNode = head;

  while (curNode)
  {
      Node* nextNode = curNode->next;
      curNode->next = prevNode;
      prevNode = curNode;
      curNode = nextNode;
  }

  return prevNode;
}

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

int main(int argc, char* argv[])
{
    vector<int> vec = {1,2,3};
    Node* head = create_linked_list(vec);
    cout << "Input linked list: ";
    print_linked_list(head);
    cout << endl;
    Node* reverse_head = Reverse(head);
    cout << "Reversed linked list: ";
    print_linked_list(reverse_head);
    cout << endl;
    return 0;
}
