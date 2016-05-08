// https://www.hackerrank.com/challenges/tree-huffman-decoding
// May 08, 2016

#include <iostream>
#include <string>

using namespace std;

typedef struct node
{
    int freq;
    char data;
    node* left;
    node* right;

}node;

node* create_huffman_tree_sample()
{
    node* node1 = new node;
    node1->data = '\0';
    node1->freq = 5;
    node1->left = NULL;
    node1->right = NULL;

    node* node2 = new node;
    node2->data = '\0';
    node2->freq = 2;
    node2->left = NULL;
    node2->right = NULL;

    node* node3 = new node;
    node3->data = 'A';
    node3->freq = 3;
    node3->left = NULL;
    node3->right = NULL;

    node* node4 = new node;
    node4->data = 'B';
    node4->freq = 1;
    node4->left = NULL;
    node4->right = NULL;

    node* node5 = new node;
    node5->data = 'C';
    node5->freq = 1;
    node5->left = NULL;
    node5->right = NULL;

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;

    return node1;
}

void decode_huff(node* root, string str)
{
    string decoded_string = "";
    unsigned int i = 0;

    while (i < str.size())
    {
        node* curNode = root;
        while (curNode->data == '\0')
        {
            if (str[i] == '0')
            {
                curNode = curNode->left;
            }
            else
            {
                curNode = curNode->right;
            }
            ++i;
        }

        decoded_string += curNode->data;
    }

    cout << decoded_string << endl;
}


int main(int argc, char* argv[])
{
    node* root = create_huffman_tree_sample();
    string str = "1001011";
    decode_huff(root, str);
    return 0;
}

