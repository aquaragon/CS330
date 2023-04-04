#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
    this->key = 0;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}
// Constructor
Node::Node(int in) {
    this->key = in;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
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
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
    if (in != nullptr)
    {
	    inorder_walk(in->get_left(), to);
	    in->print_info(to);
	    inorder_walk(in->get_right(), to);
    }
}
// Constructor
BST::BST()
{
    root = nullptr;
}
// Destructor
BST::~BST()
{
    while(root != nullptr)
    {
	    delete_node(root);
    }
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
    Node * y = nullptr;
    Node * x = this->root;
    while( x != nullptr)
    {
	    y = x;
	    if(in->get_key() < x->get_key())
	    {
		    x = x->get_left();
	    }else
	    {
		    x = x->get_right();
	    }
    }
    in->add_parent(y);
    if (y == nullptr)
    {
	    this->root = in;
    } else {
	    if(in->get_key() < y->get_key())
    		{
	    	y->add_left(in);
    	}else
    	{
	    y->add_right(in);
    	}
    }

}

void BST::transplant(Node* u, Node* v){
	if (u->get_parent() == nullptr) 
	{
		root = v;
	}
	else if (u == u->get_parent()->get_left()) 
	{
		u->get_parent()->add_left(v);
	}
	else
	{
		u->get_parent()->add_right(v);
	}
	if (v != nullptr) {
		v->add_parent(u->get_parent());
	}


}

// Delete a node to the subtree
void BST::delete_node(Node* out)
{

    if (out->get_left() == nullptr) {
	    transplant(out, out->get_right());
    }
    else if (out->get_right() == nullptr) {
	    transplant(out, out->get_left());
    }
    else {
	   Node * y = get_min(out->get_right());
    	if (y != out->get_right())
	{
		transplant(y, y->get_right());
		y->add_right(out->get_right());
		y->get_right()->add_parent(y);
	}
	transplant(out, y);
	y->add_left(out->get_left());
	y->get_left()->add_parent(y);
    }
	delete out;  
}
// minimum key in the BST
Node* BST::tree_min()
{
    return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
    return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
    while(in->get_left() != nullptr)
    {
	    in = in->get_left();
    }
    return in;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
    while(in->get_right()!= nullptr)
    {
	    in = in->get_right();
    }
    return in;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
    if (in->get_key() != tree_max()->get_key())
    {
    	if (in->get_right() != nullptr) 
    	{
		return get_min(in->get_right());
    	}
    	Node * y = in->get_parent();
    	while (y != nullptr && in == y->get_right())
    	{
	    	in = y;
	    	y = y->get_parent();
    	}
    	return y;
    }
    else{
	    return nullptr;
    }
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
   Node * curr = in;

   if(curr == tree_min()) {
	   return nullptr;
   }

   if(curr->get_left() != nullptr) {
	   return get_max(curr->get_left());
   }

   Node * y = curr->get_parent();
   while ((y != nullptr) && (curr == y->get_left())) {
	   curr = y;
	   y = y->get_parent();
   }

   return y;

}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
    inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
    if (root == nullptr)
    {
	    return nullptr;
    }else
    {
	    Node * curr = root;
	    while (curr != nullptr && curr->get_key() != search_key)
	    {
		    if (curr->get_key() > search_key)
		    {
			    curr = curr->get_left();
		    } else
		    {
			    curr = curr->get_right();
		    }
	    }
	    return curr;
    }
}
// ---------------------------------------