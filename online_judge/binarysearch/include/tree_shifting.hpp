#ifndef TREE_SHIFTING_HPP
#define TREE_SHIFTING_HPP

#include <bits/stdc++.h>

using namespace std;

class Tree {
public:
    int val;
    Tree *left;
    Tree *right;
};

Tree* solve(Tree* root);

#endif // TREE_SHIFTING_HPP
