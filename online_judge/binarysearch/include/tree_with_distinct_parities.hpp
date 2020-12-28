#ifndef TREE_WITH_DISTINCT_PARITIES_HPP
#define TREE_WITH_DISTINCT_PARITIES_HPP

#include <bits/stdc++.h>

class Tree{
    public:
        int val;
        Tree* left;
        Tree* right;
};

int solve(Tree* root);
std::pair<int, int> compute_parities(Tree* node);

#endif // TREE_WITH_DISTINCT_PARITIES_HPP
