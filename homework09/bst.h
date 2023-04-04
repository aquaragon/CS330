#ifndef BST_H_
#define BST_H_

#include <iostream>

using namespace std;



class Node {
private:
    int key;
    Node* parent;
    Node* left;
    Node* right;
public:
    // Default constructor
    Node();
    // Constructor
    Node(int in);
    // Destructor
    // a virtual constructor is required for inheritance
    virtual ~Node();

    // Add to parent of current node
    void add_parent(Node* in);
    // Add to left of current node
    void add_left(Node* in);
    // Add to right of current node
    void add_right(Node* in);

    // Get key
    int get_key();
    // Get parent node
    Node* get_parent();
    // Get left node
    Node* get_left();
    // Get right node
    Node* get_right();

    virtual void print_info(ostream& to);
};

class BST {
// private:
protected:
    Node* root;
    // Walk the subtree from the given node
    void inorder_walk(Node* in, ostream& to, Node* nilptr = nullptr);
    // Get the minimum node from the subtree of given node
    Node* get_min(Node* in, Node* nilptr = nullptr);
    // Get the maximum node from the subtree of given node
    Node* get_max(Node* in, Node* nilptr = nullptr);
    // void inorder_free(Node* in);
public:
    // Constructor and Destructor
    BST(Node* nilptr = nullptr);
    ~BST();

    // Modify tree
    void insert_node(Node* in, Node* nilptr = nullptr);
    void delete_node(Node* out, Node* nilptr = nullptr);

    // Find nodes in the tree
    Node* tree_min(Node* nilptr = nullptr); // minimum key value
    Node* tree_max(Node* nilptr = nullptr); // maximum key value
    Node* get_succ(Node* in, Node* nilptr = nullptr); // successor for a node
    Node* get_pred(Node* in, Node* nilptr = nullptr); // predecessor for a node
    void walk(ostream& to); // Traverse the tree from min to max recursively
    Node* tree_search(int search_key, Node* nipltr = nullptr);
};


void inorder_free(Node* in, Node* nilptr = nullptr);
#endif
