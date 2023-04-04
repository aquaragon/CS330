#include "db.h"
// ---------------------------------------------
// SNode class
// Default constructor
// TODO: Implement this
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 
SNode::SNode() : Node()
{
    num_students++;
}

// Constructor
// TODO: Implement this
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 
SNode::SNode(string f_, string l_, unsigned int a_) : Node(num_students)
{
    this->first = f_;
    this->last = l_;
    this->age = a_;
    num_students++;
}
// Destructor
SNode::~SNode()
{
// TODO: Implement this

}

unsigned int SNode::num_students = 0;

// Public interface
void SNode::change_first(string f_)
{
// TODO: Implement this
    this->first = f_;
} 
void SNode::change_last(string l_)
{
// TODO: Implement this
    this->last = l_;
} 
string SNode::get_first()
{
// TODO: Implement this
    return this->first;
}
string SNode::get_last()
{
// TODO: Implement this
    return this->last;
}
unsigned int SNode::get_age()
{
// TODO: Implement this
    return this->age;
}
// Print information about the student
// do not change this
void SNode::print_info(ostream& to)
{
    to << "Student ID: " << this->get_key()
       << "\tFirst: " << this->first
       << "\tLast: " << this->last
       << "\tAge: " << this->age << endl;
}
// ---------------------------------------------
