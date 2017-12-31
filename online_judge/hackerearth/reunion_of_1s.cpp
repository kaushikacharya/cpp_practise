// https://www.hackerearth.com/challenge/hiring/practo-developer-hiring-challenge/algorithm/reunion-of-1s-1b5bd063/
// Dec 20, 2017

#include <bits/stdc++.h>

using namespace std;

/*
Solved using Red-Black tree. Each node of the tree represents sub-array with all 1's i.e. start index of the sub-array and length of the sub-array
*/

const bool READ_FROM_FILE = false;
enum Color {red, black};

template<typename T>
struct RBNode
{
    // https://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct
    RBNode()
    : left(nullptr), right(nullptr), parent(nullptr){}

    RBNode(RBNode<T>* left, RBNode<T>* right, RBNode<T>* parent)
    : left(left), right(right), parent(parent){}

    Color color;
    pair<T,T> key; // pair of start index and length of sub-array of 1s
    RBNode<T>* left;
    RBNode<T>* right;
    RBNode<T>* parent;
};

template<typename T>
class RBTree
{
public:
    RBTree()
    : root_(nullptr)
    {
        nil_node_ = create_sentinel_node();
    }

    RBNode<T>* root()
    {
        return root_;
    }

    RBNode<T>* nil_node()
    {
        return nil_node_;
    }

    // Based on Cormen's advice creating a single NIL node
    // Leaf node is assigned a sentinel node
    RBNode<T>* create_sentinel_node()
    {
        RBNode<T>* sentinel_node = new RBNode<T>();
        // using sub-array length=0 for sentinel node
        sentinel_node->key = make_pair(numeric_limits<T>::max(),0);
        // leaves should be black as per red black tree properties
        sentinel_node->color = black;
        return sentinel_node;
    }

    bool is_leaf(RBNode<T>* node)
    {
        // sentinel value: sub-array length=0
        return node->key.second == 0;
    }

    RBNode<T>* parent(RBNode<T>* node)
    {
        return node->parent;
    }

    RBNode<T>* grandparent(RBNode<T>* node)
    {
        if (node->parent)
        {
            return node->parent->parent;
        }
        else
        {
            return nullptr;
        }
    }

    RBNode<T>* sibling(RBNode<T>* node)
    {
        if (node->parent)
        {
            if (node == node->parent->left)
            {
                return node->parent->right;
            }
            else
            {
                return node->parent->left;
            }
        }
        else
        {
            return nullptr;
        }
    }

    RBNode<T>* uncle(RBNode<T>* node)
    {
        if (node->parent)
        {
            return sibling(node->parent);
        }
        else
        {
            return nullptr;
        }
    }

    void rotate_left(RBNode<T>* node)
    {
        RBNode<T>* subtree_parent = node->parent;
        RBNode<T>* nodeNew = node->right;
        // TODO assert to check that nodeNew isn't a leaf node
        node->right = nodeNew->left;
        nodeNew->left = node;
        node->parent = nodeNew;
        nodeNew->left = node;
        nodeNew->parent = subtree_parent;

        if (subtree_parent)
        {
            if (subtree_parent->left == node)
            {
                subtree_parent->left = nodeNew;
            }
            else
            {
                subtree_parent->right = nodeNew;
            }
        }
    }

    void rotate_right(RBNode<T>* node)
    {
        RBNode<T>* subtree_parent = node->parent;
        RBNode<T>* nodeNew = node->left;
        // TODO assert to check that nodeNew is not a lead node
        node->left = nodeNew->right;
        nodeNew->right = node;
        node->parent = nodeNew;
        nodeNew->parent = subtree_parent;

        if (subtree_parent)
        {
            if (subtree_parent->left == node)
            {
                subtree_parent->left = nodeNew;
            }
            else
            {
                subtree_parent->right = nodeNew;
            }
        }
    }

    RBNode<T>* successor(RBNode<T>* node)
    {
        if (is_leaf(node->right))
        {
            // Find the lowest ancestor whose left child descendant contains node
            while ((parent(node) != nullptr) && (parent(node)->right == node))
            {
                node = parent(node);
            }

            return parent(node);
        }
        else
        {
            // successor is the smallest value node in sub-tree with right child of node as root
            node = node->right;

            while (!is_leaf(node->left))
            {
                node = node->left;
            }

            return node;
        }
    }

    // insert
    void insert_node(RBNode<T>* node)
    {
        // First place the node in tree
        insert_node_in_tree(node);

        // Repair the tree in case any of the red-black properties have been violated
        insert_repair_tree(node);

        // update the new root
        // Note: unlike Cormen's algo, this implementation has root's parent as null
        RBNode<T>* cur_node = node;
        while (cur_node->parent)
        {
            cur_node = cur_node->parent;
        }
        root_ = cur_node;
    }

    // inserts node in the tree similar to as done in BST
    void insert_node_in_tree(RBNode<T>* node)
    {
        RBNode<T>* cur_node = root();

        while (cur_node)
        {
            if (node->key.first < cur_node->key.first)
            {
                if (!is_leaf(cur_node->left))
                {
                    cur_node = cur_node->left;
                }
                else
                {
                    cur_node->left = node;
                    break;
                }
            }
            else
            {
                if (!is_leaf(cur_node->right))
                {
                    cur_node = cur_node->right;
                }
                else
                {
                    cur_node->right = node;
                    break;
                }
            }
        }

        node->parent = cur_node;
        // assigning Leaf(nil) node in place of null
        if (node->left == NULL)
        {
            node->left = nil_node();
        }
        if (node->right == NULL)
        {
            node->right = nil_node();
        }
        node->color = red;
    }

    void insert_repair_tree(RBNode<T>* node)
    {
        // Four cases

        if (!node->parent)
        {
            // case 1: node is at the root
            node->color = black;
            // cout << "\t case 1: insert_repair_tree" << endl;
        }
        else if (parent(node)->color == black)
        {
            // case 2: red-black tree properties haven't been violated
            // In rest of the two cases, parent is red
            // cout << "\t case 2: insert_repair_tree" << endl;
            return;
        }
        else if (uncle(node)->color == red)
        {
            // case 3: Both parent and uncle are red
            // cout << "\t case 3: insert_repair_tree" << endl;
            parent(node)->color = black;
            uncle(node)->color = black;
            grandparent(node)->color = red;
            // as red-black properties might have got violated due to above color change, hence fix by passing grandparent
            insert_repair_tree(grandparent(node));
        }
        else
        {
            // case 4: Parent is red but uncle is black
            // cout << "\t case 4: insert_repair_tree" << endl;

            // step 1: if node is on the "inside" of the subtree under grandparent then switch the role of node and its parent
            if (node == grandparent(node)->left->right)
            {
                rotate_left(parent(node));
                node = node->left;
            }
            else if (node == grandparent(node)->right->left)
            {
                rotate_right(parent(node));
                node = node->right;
            }

            // step 2: Above step ensures that current node is on the "outside" of the subtree under grandparent
            //         Note that if node was "inside" it has been swapped with its parent after the rotation
            RBNode<T>* node_p = parent(node);
            RBNode<T>* node_g = grandparent(node);
            assert((node_g != NULL) && "insert_repair_tree(): case 4 step 2:: grandparent is null");

            if (node == parent(node)->left)
            {
                rotate_right(node_g);
            }
            else
            {
                rotate_left(node_g);
            }

            node_p->color = black;
            node_g->color = red;
        }
    }

    // delete
    void delete_node(RBNode<T>* node)
    {
        // If both the children of the given node are non-leaf then we replace the contents of given node with its successor node and
        //  delete the successor node. Thus it becomes a problem of deleting a node which has at least one child as leaf node.
        RBNode<T>* y_node = nullptr;
        if ( (is_leaf(node->left)) || (is_leaf(node->right)) )
        {
            y_node = node;
        }
        else
        {
            y_node = successor(node);
        }
        assert(( (is_leaf(y_node->left)) || (is_leaf(y_node->right)) ) && "y_node has both non-leaf children");

        // x_node is the child node of y_node which is going to be linked with parent of y_node
        RBNode<T>* x_node = nullptr;
        if (!is_leaf(y_node->left))
        {
            x_node = y_node->left;
        }
        else
        {
            x_node = y_node->right;
        }

        x_node->parent = y_node->parent;
        if (!(y_node->parent))
        {
            root_ = x_node;
        }
        else if (y_node == y_node->parent->left)
        {
            y_node->parent->left = x_node;
        }
        else
        {
            y_node->parent->right = x_node;
        }

        if (y_node != node)
        {
            node->key = y_node->key;
        }

        if (y_node->color == black)
        {
            delete_fixup(x_node);
        }

        delete y_node;
    }

    // Fix the violations of RB tree
    void delete_fixup(RBNode<T>* node_x)
    {
        while ( (node_x != root_) && (node_x->color == black) )
        {
            // Note: unlike insertion cases, deletion cases aren't mutually exclusive
            // case 1: node_x is black but its sibling is red
            // case 2: sibling of  node_x is black and both children of the sibling are also black
            // case 3:
            // case 4:

            RBNode<T>* node_w = sibling(node_x); // sibling of node_x
            if (node_x == node_x->parent->left)
            {
                // case #1
                if (node_w->color == red)
                {
                    node_w->color = black;
                    node_x->parent->color = red;
                    rotate_left(node_x->parent);
                    node_w = node_x->parent->right;
                }

                if ( (node_w->left->color = black) && (node_w->right->color == black) )
                {
                    // case #2
                    node_w->color = red;
                    node_x = node_x->parent;
                }
                else
                {
                    if (node_w->right->color == black)
                    {
                        // case #3
                        node_w->left->color = black;
                        node_w->color = red;
                        rotate_right(node_w);
                        // assign sibling after the rotation
                        node_w = node_x->parent->right;
                    }

                    assert(node_w->right->color == red);
                    // case #4
                    node_w->color = node_x->parent->color;
                    node_x->parent->color = black;
                    node_w->right->color = black;
                    rotate_left(node_x->parent);
                    root_ = node_x;
                    root_->parent = nullptr; // As per the notation we have followed
                }
            }
            else
            {
                // node_x is right child of its parent

                // case #1
                if (node_w->color == red)
                {
                    node_w->color = black;
                    node_x->parent->color = red;
                    rotate_right(node_x->parent);
                    node_w = node_x->parent->left;
                }

                if ( (node_w->left->color = black) && (node_w->right->color == black) )
                {
                    // case #2
                    node_w->color = red;
                    node_x = node_x->parent;
                }
                else
                {
                    if (node_w->left->color == black)
                    {
                        // case #3
                        node_w->right->color = black;
                        node_w->color = red;
                        rotate_left(node_w);
                        // assign sibling after the rotation
                        node_w = node_x->parent->left;
                    }

                    assert(node_w->left->color == red);
                    // case #4
                    node_w->color = node_x->parent->color;
                    node_x->parent->color = black;
                    node_w->left->color = black;
                    rotate_right(node_x->parent);
                    root_ = node_x;
                    root_->parent = nullptr; // As per the notation we have followed
                }
            }

        }

        node_x->color = black;
    }
private:
    RBNode<T>* root_;
    RBNode<T>* nil_node_;
};

// Checks which are the sub-arrays of 1s
template<typename T>
class ReUnion
{
public:
    ReUnion(string str)
    : str_(str)
    {
        max_len_sub_array_ = 0;
        initialize_rb_tree();
    }

    // add nodes of sub-arrays of 1s from the original string given at beginning
    void initialize_rb_tree()
    {
        T sub_array_start_index;
        T sub_array_length = 0;

        for (T i=0; i != str_.length(); ++i)
        {
            if (str_[i] == '1')
            {
                if ( (i > 0) && (str_[i-1] == '1') )
                {
                    // inside sub-array of 1s
                    ++sub_array_length;
                }
                else
                {
                    // start of sub-array of 1s
                    sub_array_start_index = i;
                    sub_array_length = 1;
                }
            }
            else
            {
                // check if sub-array of 1s has just ended
                if ( (i > 0) && (str_[i-1] == '1') )
                {
                    RBNode<T>* node = new RBNode<T>(rb_tree_.nil_node(), rb_tree_.nil_node(), nullptr);
                    node->key = make_pair(sub_array_start_index, sub_array_length);
                    node->color = red;
                    rb_tree_.insert_node(node);

                    max_len_sub_array_ = max(max_len_sub_array_, sub_array_length);
                }
                // assigning sub-array length of 1s as zero till we find the next '1'
                sub_array_length = 0;
            }
        }

        // check if the last sub-array of 1s was till the str_ end
        if (sub_array_length > 0)
        {
            RBNode<T>* node = new RBNode<T>(rb_tree_.nil_node(), rb_tree_.nil_node(), rb_tree_.nil_node());
            node->key = make_pair(sub_array_start_index, sub_array_length);
            node->color = red;
            rb_tree_.insert_node(node);

            max_len_sub_array_ = max(max_len_sub_array_, sub_array_length);
        }
    }

    // change str_[pos] to '1'
    // If neighboring position(s) also has '1' then we need to update those sub-array(s) and re-compute max length sub-array
    void update_character(T pos)
    {
        if (str_[pos] == '1')
        {
            // Nothing needs to be done as the character at the given position is already '1'
            return;
        }

        // change '0' to '1' at the given position
        str_[pos] = '1';

        // Four cases are possible:
        // case 1: New sub-array of length=1 starting at pos will be created.
        // case 2: pos will extend the sub-array at its left.
        // case 3: pos will extend the sub-array at its right.
        // case 4: pos will merge the sub-arrays at its left and right.

        if ( ( (pos == 0) || (str_[pos-1] == '0') ) && ( (pos == (str_.size()-1)) || (str_[pos+1] == '0') ) )
        {
            // case 1: new sub-array needs to be created
            RBNode<T>* node = new RBNode<T>(rb_tree_.nil_node(), rb_tree_.nil_node(), rb_tree_.nil_node());
            T sub_array_length = 1;
            node->key = make_pair(pos, sub_array_length);
            node->color = red;
            rb_tree_.insert_node(node);
            // update max length of sub-array of 1s
            max_len_sub_array_ = max(max_len_sub_array_, sub_array_length);
        }
        else if ( (pos > 0) && (pos < (str_.size()-1)) && (str_[pos-1] == '1') && (str_[pos+1] == '1') )
        {
            // case 4: merge
            cout << "\tcase 4: merge" << endl;

            // 1. extend the left sub-array node till the right sub-array node
            // 2. delete the right sub-array node
            RBNode<T>* left_node = get_left_sub_array_node(pos);
            RBNode<T>* right_node = get_right_sub_array_node(pos);

            left_node->key.second += 1 + right_node->key.second;
            rb_tree_.delete_node(right_node);

            // update max length of sub-array of 1s
            max_len_sub_array_ = max(max_len_sub_array_, left_node->key.second);
        }
        else if ( (pos > 0) && (str_[pos-1] == '1') )
        {
            // case 2: extend left sub-array to pos
            RBNode<T>* left_node = get_left_sub_array_node(pos);
            // update key
            left_node->key.second += 1;

            // update max length of sub-array of 1s
            max_len_sub_array_ = max(max_len_sub_array_, left_node->key.second);
        }
        else
        {
            assert(pos < (str_.size()-1));
            // case 3: pre-pend right sub-array with pos
            RBNode<T>* right_node = get_right_sub_array_node(pos);
            // update key
            right_node->key.first -= 1; // shifting start index of sub-array to left
            right_node->key.second += 1;

            // update max length of sub-array of 1s
            max_len_sub_array_ = max(max_len_sub_array_, right_node->key.second);
        }
    }

    // Get the left sub-array node which can be extended to pos
    // Assumption: 1. pos is not yet part of any sub-array
    //             2. There exists a sub-array which can be extended to pos
    RBNode<T>* get_left_sub_array_node(T pos)
    {
        RBNode<T>* cur_node = rb_tree_.root();
        while (true)
        {
            // assert(cur_node != rb_tree_.nil_node());
            T start_index = cur_node->key.first;
            T sub_array_size = cur_node->key.second;
            cout << "\t(left) cur_node range: [" << start_index << "," << start_index+sub_array_size << ")" << endl;

            if (pos == (start_index+sub_array_size))
            {
                break;
            }

            if (start_index < pos)
            {
                cur_node = cur_node->right;
            }
            else
            {
                cur_node = cur_node->left;
            }
        }

        return cur_node;
    }

    // Get the right sub-array node to which pos can prepended
    // Assumption: 1. pos is not yet part of any sub-array
    //             2. There exists a sub-array which can be extended from pos
    RBNode<T>* get_right_sub_array_node(T pos)
    {
        RBNode<T>* cur_node = rb_tree_.root();
        while (true)
        {
            assert(cur_node != rb_tree_.nil_node());
            T start_index = cur_node->key.first;
            T sub_array_size = cur_node->key.second;
            cout << "\t(right) cur_node range: [" << start_index << "," << start_index+sub_array_size << ")" << endl;

            if (pos == (start_index-1))
            {
                break;
            }

            if (start_index < pos)
            {
                cur_node = cur_node->right;
            }
            else
            {
                cur_node = cur_node->left;
            }
        }

        return cur_node;
    }

    T max_len_sub_array()
    {
        return max_len_sub_array_;
    }

    // in-order traversal for checking validity of BST
    bool check_bst_validity()
    {
        T i = 0;
        T sub_array_start_index;
        T sub_array_length = 0;
        bool is_match = true;

        cout << "\troot: sub_array_start_index: " << rb_tree_.root()->key.first << " : sub_array_length: " << rb_tree_.root()->key.second << endl;
        if (rb_tree_.is_leaf(rb_tree_.root()->left))
        {
            cout << "\tleft of root is leaf" << endl;
        }
        if (rb_tree_.is_leaf(rb_tree_.root()->right))
        {
            cout << "\tright of root is leaf" << endl;
        }
        stack<pair<RBNode<T>*,bool> > stk;
        stk.push(make_pair(rb_tree_.root(), false));

        while (!stk.empty())
        {
            pair<RBNode<T>*,bool> cur_elem = stk.top();
            RBNode<T>* cur_node = cur_elem.first;
            bool is_visited = cur_elem.second;
            cout << "\tstack top: [" << cur_node->key.first << "," << cur_node->key.first+cur_node->key.second << "): " << is_visited << endl;
            // pop from top of the stack
            stk.pop();

            if (is_visited)
            {
                // cur_node's children have already been pushed into stack in an earlier iteration

                // get the next sub-array of 1s by traversing the string and check if that matches with the one in cur_node
                while (i < str_.length())
                {
                    if (str_[i] == '1')
                    {
                        if ( (i > 0) && (str_[i-1] == '1') )
                        {
                            // inside sub-array of 1s
                            ++sub_array_length;
                        }
                        else
                        {
                            // start of sub-array of 1s
                            sub_array_start_index = i;
                            sub_array_length = 1;
                        }
                    }
                    else
                    {
                        // check if sub-array of 1s has just ended
                        if ( sub_array_length > 0 )
                        {
                            if ((sub_array_start_index != cur_node->key.first) || (sub_array_length != cur_node->key.second))
                            {
                                // mismatch
                                is_match = false;
                                cout << "\tmismatch: node: [" << cur_node->key.first << "," << cur_node->key.first+cur_node->key.second
                                << ") :: string: [" << sub_array_start_index << "," << sub_array_start_index+sub_array_length << ")" << endl;
                            }
                            else
                            {
                                cout << "\tmatch: string: [" << sub_array_start_index << "," << sub_array_start_index+sub_array_length << ")" << endl;
                            }

                            // assigning sub-array length of 1s as zero till we find the next '1'
                            sub_array_length = 0;
                            break;
                        }
                    }

                    ++i;
                }

                // check if the last sub-array of 1s was till the str_ end
                if (sub_array_length > 0)
                {
                    if ((sub_array_start_index != cur_node->key.first) || (sub_array_length != cur_node->key.second))
                    {
                        // mismatch
                        is_match = false;
                        cout << "\tmismatch: node: [" << cur_node->key.first << "," << cur_node->key.first+cur_node->key.second
                        << ") :: string: [" << sub_array_start_index << "," << sub_array_start_index+sub_array_length << ")" << endl;
                    }
                    else
                    {
                        cout << "\tmatch: string: [" << sub_array_start_index << "," << sub_array_start_index+sub_array_length << ")" << endl;
                    }
                }

                if (!is_match)
                {
                    break; // break the outer loop
                }
            }
            else
            {
                if(!rb_tree_.is_leaf(cur_node->right))
                {
                    stk.push(make_pair(cur_node->right, false));
                }
                stk.push(make_pair(cur_node, true));
                if(!rb_tree_.is_leaf(cur_node->left))
                {
                    stk.push(make_pair(cur_node->left, false));
                }
            }
        }

        return is_match;
    }

private:
    RBTree<T> rb_tree_;
    string str_;
    T max_len_sub_array_;
};

void string_iteration_test()
{
   string str = "00100";
    for (unsigned long ch_i=0; ch_i != str.length(); ++ch_i)
    {
        cout << ch_i << ": " << str[ch_i] << endl;
    }
}

void tree_node_null_test(bool is_non_null_root = false)
{
    RBTree<unsigned long>* rb_tree = new RBTree<unsigned long>();
    if (is_non_null_root)
    {
        RBNode<unsigned long>* rb_node = new RBNode<unsigned long>(rb_tree->nil_node(), rb_tree->nil_node(), nullptr);
        // RBNode<unsigned long>* rb_node = new RBNode<unsigned long>(nullptr, nullptr, nullptr);
        rb_node->key = make_pair(0,1);
        rb_tree->insert_node(rb_node);
    }

    if (rb_tree->root())
    {
        cout << "case1: non null root" << endl;
    }
    if (rb_tree->root() != NULL)
    {
        cout << "case2: non null root" << endl;
    }
    if (rb_tree->root() != nullptr)
    {
        cout << "case3: non null root" << endl;
    }
    if (!rb_tree->root())
    {
        cout << "null root" << endl;
    }
}

int main(int argc, char* argv[])
{
    // string_iteration_test();
    // tree_node_null_test(true);

    unsigned long n,k;
    string str;

    fstream pFile;

    if (READ_FROM_FILE)
    {
        pFile.open("C:/KA/personal/cpp_practise/online_judge/hackerearth/input/5542ff66d34011e7.txt.clean.txt", ios::in);
        assert(pFile.is_open() && "file not openend");
    }
    if (READ_FROM_FILE)
    {
        pFile >> n;
        pFile >> k;
        pFile >> str;
    }
    else
    {
        cin >> n;
        cin >> k;
        cin >> str;
    }

    ReUnion<unsigned long> reunion(str);

    unsigned long pos;
    char ch;
    for (unsigned long i=0; i != k; ++i)
    {
        if (READ_FROM_FILE)
        {
            pFile >> ch;
        }
        else
        {
            cin >> ch;
        }
        // cout << "ch: " << ch << endl;
        cout << "query #" << i << endl;

        if (ch == '1')
        {
            // print the length of longest sub-array of 1s
            unsigned long max_len_sub_array = reunion.max_len_sub_array();
            cout << max_len_sub_array << endl;
        }
        else
        {
            if (READ_FROM_FILE)
            {
                pFile >> pos;
            }
            else
            {
                cin >> pos;
            }
            // cout << "pos: " << pos << endl;
            reunion.update_character(pos-1); // subtracting 1 as we are using 0-indexed
            bool is_match = reunion.check_bst_validity();
            if (!is_match)
            {
                break;
            }
        }
    }

    if(READ_FROM_FILE)
    {
        pFile.close();
    }

    return 0;
}

/***
Reference:

Red-Black tree:
For insertion followed https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
For deletion followed CLRS book

Current Status:

Failing in most of the test cases. Instead of implementing red-black tree, better to use set of stl which is an implementation of red-black tree.
*/
