#ifndef DIAGONAL_TREE_TRAVERSAL_HPP
#define DIAGONAL_TREE_TRAVERSAL_HPP

#include <bits/stdc++.h>

using namespace std;

class Tree{
    public:
        int val;
        Tree* left;
        Tree* right;
};

vector<int> solve(Tree*);

#endif // DIAGONAL_TREE_TRAVERSAL_HPP
