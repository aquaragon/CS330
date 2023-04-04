#ifndef NUMLIST_H_
#define NUMLIST_H_

#include <iostream>
#include <vector>

using namespace std;


enum ImplType { 
    serial, 
    parallel 
};

// Wrapper class for vector of integers
class NumList {
    // list of numbers
    vector<int> list;
    // quick sort functions
    // these are private since the user should not need to call this
    unsigned int partition(vector<int>& keys, unsigned int low, 
                           unsigned int high);
    unsigned int partition_par(vector<int>& keys, unsigned int low,
                                         unsigned int high);
    void qsort(vector<int>& keys, int low, int high, ImplType opt);
    void my_qsort(ImplType opt); // wrapper for sorting the list
public:
    // Constructors
    NumList();
    NumList(vector<int> in, ImplType opt);
    // Destructor
    ~NumList();

    // Member functions
    int get_elem(unsigned int index);
    void print(ostream& os);
};

#endif
