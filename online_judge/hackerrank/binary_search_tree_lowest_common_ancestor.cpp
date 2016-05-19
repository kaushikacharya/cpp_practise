// https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor
// May 13, 2016

#include <iostream>

using namespace std;

typedef struct node
{
    int data;
    node* left;
    node* right;
} node;

node* lca(node* root, int v1, int v2)
{
    int v_lower = (v1 <= v2)? v1:v2;
    int v_upper = (v1 <= v2)? v2:v1;

    node* lca_node = root;

    while (true)
    {
        if ((v_lower <= lca_node->data) && (v_upper >= lca_node->data))
        {
            // Handles both cases:
            // case #1: v_lower is in left subtree and v_upper is in right subtree
            // case #2: either of v_lower or v_upper is same as lca_node
            break; // lca_node is the lowest common ancestor
        }
        else if (v_upper < lca_node->data)
        {
            lca_node = lca_node->left;
        }
        else
        {
            lca_node = lca_node->right;
        }
    }

    return lca_node;
}

node* create_bst()
{
    node* node1 = new node;
    node1->data = 1;
    node* node2 = new node;
    node2->data = 2;
    node* node3 = new node;
    node3->data = 3;
    node* node4 = new node;
    node4->data = 4;
    node* node6 = new node;
    node6->data = 6;
    node* node7 = new node;
    node7->data = 7;

    node4->left = node2;
    node4->right = node7;
    node2->left = node1;
    node2->right = node3;
    node7->left = node6;

    return node4;
}

int main(int argc, char* argv[])
{
    node* root = create_bst();
    int v1 = 4;
    int v2 = 2;
    node* lca_node = lca(root, v1, v2);
    cout << "lowest common ancestor: " << lca_node->data << endl;
    return 0;
}
