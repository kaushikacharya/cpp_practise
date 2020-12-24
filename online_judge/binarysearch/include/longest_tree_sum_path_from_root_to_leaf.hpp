#ifndef LONGEST_TREE_SUM_PATH_FROM_ROOT_TO_LEAF_HPP
#define LONGEST_TREE_SUM_PATH_FROM_ROOT_TO_LEAF_HPP

#include <bits/stdc++.h>

class Tree{
    public:
        int val;
        Tree* left;
        Tree* right;
};

int solve(Tree* root);

#endif // LONGEST_TREE_SUM_PATH_FROM_ROOT_TO_LEAF_HPP
