#ifndef RBT_H_
#define RBT_H_

#include <iostream>
#include "bst.h"

using namespace std;

enum Node_color {
    RED,
    BLACK
};

class RBTNode : public Node {
private:
   Node_color color;
   void print_color(ostream& to); 
public:
    // Default constructor
    RBTNode();
    // Constructor
    RBTNode(int in);
    // Destructor
    // a virtual destructor is required for inheritance
    ~RBTNode();

    // change the color of this node
    Node_color get_color();
    void add_color(Node_color c);

    void print_info(ostream& to);
};

class RBT : public BST {
private:
    RBTNode* sentinel;
public:
    // Constructor and Destructor
    RBT();
    ~RBT();

    // helper functions
    // these can normally be made private - but they are public here
    // so that we can do a unit test on these functions
    void right_rotate(RBTNode* x);
    void left_rotate(RBTNode* x);
    void rb_insert_fixup(RBTNode* x);
    void rb_delete_fixup(RBTNode* x);

    // These functions need to implemented as it is different from a BST
    // Modify tree
    void rb_insert_node(RBTNode* in);
    void rb_delete_node(RBTNode* out);

    // Wrapper for existing functions in BST
    RBTNode* tree_min(); // minimum key value
    RBTNode* tree_max(); // maximum key value
    RBTNode* get_succ(RBTNode* in); // successor for a given node
    RBTNode* get_pred(RBTNode* in); // predecessor for a given node
    void walk(ostream& to); // traverse the tree from min to max recursively 
    RBTNode* tree_search(int search_key); // return the first node with search_key

    RBTNode* get_sentinel() { return sentinel; }
};
#endif
