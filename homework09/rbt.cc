#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */
    RBTNode * x = dynamic_cast<RBTNode*>(y->get_left());
    y->add_left(x->get_right());
    if (x->get_right() != sentinel)
    {
        x->get_right()->add_parent(y);
    }
    x->add_parent(y->get_parent());
    if (y->get_parent() == sentinel)
    {
        root = x;
    }else if (y == y->get_parent()->get_right())
    {
        y->get_parent()->add_right(x);
    }else
        y->get_parent()->add_left(x);
    x->add_right(y);
    y->add_parent(x);
}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* TODO */
    RBTNode * y = dynamic_cast<RBTNode*>(x->get_right());
    x->add_right(y->get_left());
    if (y->get_left() != sentinel)
    {
        y->get_left()->add_parent(x);
    }
    y->add_parent(x->get_parent());
    if(x->get_parent() == sentinel)
    {
        root = y;
    }
    else if (x == x->get_parent()->get_left())
    {
        x->get_parent()->add_left(y);
    }else
    {
        x->get_parent()->add_right(y);
    }
    y->add_left(x);
    x->add_parent(y);
}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */
    RBTNode * in_parent = dynamic_cast<RBTNode*>(in->get_parent());
    while (in != root && in_parent->get_color() == RED)
        {
            RBTNode * grand_parent = dynamic_cast<RBTNode*>(in_parent->get_parent());
            if (in_parent == grand_parent->get_left())
            {
                RBTNode* uncle = dynamic_cast<RBTNode*>(grand_parent->get_right());
                if (uncle != sentinel && uncle->get_color() == RED)
                {
                    in_parent->add_color(BLACK);
                    uncle->add_color(BLACK);
                    grand_parent->add_color(RED);
                    in = grand_parent;
                }
                else 
                {
                    if (in == in_parent->get_right())
                    {
                        in = in_parent;
                        left_rotate(in);
                    }
                    in_parent->add_color(BLACK);
                    grand_parent->add_color(RED);
                    right_rotate(grand_parent);
                }
            }
            else 
            {
                RBTNode* uncle = dynamic_cast<RBTNode*>(grand_parent->get_left());
                if (uncle != sentinel && uncle->get_color() == RED)
                {
                    in_parent->add_color(BLACK);
                    uncle->add_color(BLACK);
                    grand_parent->add_color(RED);
                    in = grand_parent;
                }
                else {
                    if (in == in_parent->get_left()) {
                        in = in_parent;
                        right_rotate(in);
                    }
                    in_parent->add_color(BLACK);
                    grand_parent->add_color(RED);
                    left_rotate(grand_parent);
                }
            }
        }
    
    RBTNode * rbtroot = dynamic_cast<RBTNode*>(root);
    rbtroot->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */
    BST::insert_node(in, sentinel);
    in->add_color(RED);
    in->add_left(sentinel);
    in->add_right(sentinel);
    rb_insert_fixup(in);

    /*
    RBTNode * x = dynamic_cast<RBTNode*>(root);
    RBTNode * y = nullptr;
    while(x != nullptr)
    {
        y = x;
        if (in->get_key() < x->get_key())
        {
            x = dynamic_cast<RBTNode*>(x->get_left());
        }else
        {
            x = dynamic_cast<RBTNode*>(x->get_right());
        }
    }
    in->add_parent(y);
    if (y == nullptr)
    {
        root = in;
    }else if (in->get_key() < y->get_key())
    {
        y->add_left(in);
    }else
    {
        y->add_right(in);
    }
    rb_insert_fixup(in);
    */
}

void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */
    RBTNode * p = dynamic_cast<RBTNode*>(in->get_parent());
    while(in != root && in->get_color() == BLACK)
    {
	if(in == p->get_left())
	{
		RBTNode * p_right = dynamic_cast<RBTNode*>(p->get_right());
		if(p_right->get_color() == RED) //case #1
		{
			p_right->add_color(BLACK);
			p->add_color(RED);
			left_rotate(p);
			p_right = dynamic_cast<RBTNode*>(p->get_right());
		}

		RBTNode * p_right_left = dynamic_cast<RBTNode*>(p_right->get_left());
		RBTNode * p_right_right = dynamic_cast<RBTNode*>(p_right->get_right());
		if (p_right_left->get_color() == BLACK && p_right_right->get_color() == BLACK) // case #2
		{
			p_right->add_color(RED);
			in = p;
		}
		else
		{
			if(p_right_right->get_color() == BLACK) // case #3
			{
				p_right_left->add_color(BLACK);
				p_right->add_color(RED);
				right_rotate(p_right);
				p_right = dynamic_cast<RBTNode*>(p->get_right());
			}
			p_right->add_color(p->get_color());
			p->add_color(BLACK);
			p_right_right->add_color(BLACK);
			left_rotate(p);
			in = dynamic_cast<RBTNode*>(root);
		}
	}
	else
	{
		RBTNode * p_left = dynamic_cast<RBTNode*>(p->get_left());
		if(p_left->get_color() == RED)
		{
			p_left->add_color(BLACK);
			p->add_color(RED);
			right_rotate(p);
			p_left = dynamic_cast<RBTNode*>(p->get_left());
		}

		RBTNode * p_left_right = dynamic_cast<RBTNode*>(p_left->get_right());
		RBTNode * p_left_left = dynamic_cast<RBTNode*>(p_left->get_left());
		if (p_left_left->get_color() == BLACK && p_left_right->get_color() == BLACK)
		{
			p_left->add_color(RED);
			in = p;
		}
		else
		{
			if(p_left_left->get_color() == BLACK)
			{
				p_left_right->add_color(BLACK);
				p_left->add_color(RED);
				left_rotate(p_left);
				p_left = dynamic_cast<RBTNode*>(p->get_left());
			}
			p_left->add_color(p->get_color());
			p->add_color(BLACK);
			p_left_left->add_color(BLACK);
			right_rotate(p);
			in = dynamic_cast<RBTNode*>(root);
		}
	}
    }
    in->add_color(BLACK);
}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */
    /*
    RBTNode * y = out;
    Node_color y_original_color = y->get_color;
    RBTNode * x = nullptr;
    if (out->get_left() == nullptr)
    {
        x = dynamic_cast<RBTNode*>(out->get_right());
    }*/
    BST::delete_node(out,sentinel);
}

// ---------------------------------------
