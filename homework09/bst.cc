#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
    this->key = 0;
    this->parent = nullptr; 
    this->left = nullptr;
    this->right = nullptr;
}
// Constructor
Node::Node(int in) {
    this->key = in;
    this->parent = nullptr; 
    this->left = nullptr;
    this->right = nullptr;
}
// Destructor
Node::~Node() {
}

// Add parent 
void Node::add_parent(Node* in) {
    this->parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
    this->left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
    this->right = in;
}

// Get key
int Node::get_key()
{
    return this->key;
}
// Get parent node
Node* Node::get_parent()
{
    return this->parent;
}
// Get left node
Node* Node::get_left()
{
    return this->left;
}
// Get right node
Node* Node::get_right()
{
    return this->right;
}

void Node::print_info(ostream& to)
{
    // to << key << endl;
    to << key;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to, Node* nilptr)
{
    if(in != nilptr) {
        inorder_walk(in->get_left(), to, nilptr);
        in->print_info(to); 
        to << endl;
        inorder_walk(in->get_right(), to, nilptr);
    }
}
// Constructor
BST::BST(Node* nilptr)
{
    root = nilptr;
}
void inorder_free(Node* in, Node* nilptr)
{
    if(in == nilptr) {
        return;
    }
    inorder_free(in->get_left(), nilptr);
    inorder_free(in->get_right(), nilptr);
    delete in;
}
// Destructor
BST::~BST()
{
    inorder_free(root);
}
// Insert a node to the subtree
void BST::insert_node(Node* in, Node* nilptr)
{
    // Node* tmp = nullptr;
    Node* tmp = nilptr;
    Node* cur = this->root;
    while(cur != nilptr) {
        tmp = cur;
        if(in->get_key() < cur->get_key()) {
            cur = cur->get_left();
        } else {
            cur = cur->get_right();
        }
    }
    in->add_parent(tmp);
    if(tmp == nilptr) {
        this->root = in;
    } else {
        if(in->get_key() < tmp->get_key()) {
            tmp->add_left(in);
        } else {
            tmp->add_right(in);
        }
    }
}
// Delete a node to the subtree
void BST::delete_node(Node* out, Node* nilptr)
{
    // temporary pointers
    Node* y = nilptr;
    Node* x = nilptr;

    // first determine if out has at most one child
    if((out->get_left() == nilptr) || (out->get_right() == nilptr)) {
        // 0 or 1 child - out will be spliced
        y = out;
    } else {
        // 2 children - out's successor will be sliced out
        y = this->get_succ(out, nilptr);
        // cout << y->get_key() << endl;
    }
 
    // set x to a non-null child of y, or null if it has no children
    // Recall that y is either out (if it has 0 or 1 child), 
    // or succ (if it has 2 children)
    // Since succ can only have 1 child, y should only have one child
    if(y->get_left() != nilptr) {
        x = y->get_left();                            
    } else {
        x = y->get_right();
    }

    // Splice out node y with its child
    // check for null, otherwise the code will segfault
    if(x != nilptr) {
        x->add_parent(y->get_parent());
    }

    
    // Extra code to account for RBT
    if(x == nilptr && x != nullptr) {
        x->add_parent(y->get_parent());
    }
    

    if(y->get_parent() == nilptr) {
        root = x;
    } else if(y == y->get_parent()->get_left()) {
        y->get_parent()->add_left(x);
    } else {
        y->get_parent()->add_right(x);
    }

    // Finally, replace out with y
    if(y != out) {
        // first copy out's parent and children to y
        y->add_parent(out->get_parent());
        if(y->get_parent() == nilptr) {
            root = y;
        } else {
            // update the parent's child to y
            if(out == out->get_parent()->get_left()) {
                y->get_parent()->add_left(y);
            } else {
                y->get_parent()->add_right(y);
            }
        }
        y->add_left(out->get_left());
        y->add_right(out->get_right());

        // update the children's parents to y
        if(y->get_left() != nilptr) {
            y->get_left()->add_parent(y);
        }
        if(y->get_right() != nilptr) {
            y->get_right()->add_parent(y);
        }
    }

    // out is no longer needed - free it
    delete out;
}
// minimum key in the BST
Node* BST::tree_min(Node* nilptr)
{
    return get_min(root, nilptr);
}
// maximum key in the BST
Node* BST::tree_max(Node* nilptr)
{
    return get_max(root, nilptr);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in, Node* nilptr)
{
    Node* cur = in;
    while(cur->get_left() != nilptr) {
        cur = cur->get_left();
    }
    return cur;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in, Node* nilptr)
{
    Node* cur = in;
     while(cur->get_right() != nilptr) {
        cur = cur->get_right();
    }
    return cur;
}
// Get successor of the given node
Node* BST::get_succ(Node* in, Node* nilptr)
{
    Node* cur = in;

    // If this node is the max node, then it has no successor
    if(cur == tree_max(nilptr)) {
        return nullptr;
    }

    // If this node has a right child, then the successor is
    // the min of the right subtree
    if(cur->get_right() != nilptr) {
        return get_min(cur->get_right(), nilptr);
    }

    // Otherwise, the successor is the node's LOWEST ancestor whose 
    // left child is also the ancestor of the node
    Node* tmp = cur->get_parent();
    while((tmp != nilptr) && (cur == tmp->get_right())) {
        cur = tmp;
        tmp = tmp->get_parent();
    }

    return tmp;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in, Node* nilptr)
{
    Node* cur = in;

    // If this node is the max node, then it has no predecessor 
    if(cur == tree_min(nilptr)) {
        return nullptr;
    }

    // If this node has a left child, then the predecessor is the
    // max of the left subtree
    if(cur->get_left() != nilptr) {
        return get_max(cur->get_left(), nilptr);
    }

    // Otherwise, the predecessor is the node's LOWEST ancestor whose
    // right child is also the ancestor of the node
    Node* tmp = cur->get_parent();
    while((tmp != nilptr) && (cur == tmp->get_left())) {
        cur = tmp;
        tmp = tmp->get_parent();
    }

    return tmp;

}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
    inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key, Node* nilptr)
{
    Node* tmp = root;
    while((tmp != nilptr) && (search_key != tmp->get_key())) {
        if(search_key < tmp->get_key()) {
            tmp = tmp->get_left(); 
        } else {
            tmp = tmp->get_right(); 
        }
    }

    return tmp;
}
// ---------------------------------------
