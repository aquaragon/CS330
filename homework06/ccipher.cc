#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation


CCipher::CCipher()
{   
}

CCipher::CCipher(int positive_shift)
{
    
    if (positive_shift >= 0)
    {
        rotate_string(this->smile->cipher_alpha, positive_shift);
    }else
    {
        cout << "ERROR: invalid shift" << endl;
        exit(EXIT_FAILURE);
    }
}

CCipher ::~CCipher() {}
// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
        // TODO: You will likely need this function. Implement it.   
        string result;

        int size = in_str.length();
        for (int i = 0; i < size; i++)
        {
            result += in_str[(i + rot) % size];
        }
        in_str = result;
}
