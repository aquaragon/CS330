#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------


RCipher::RCipher()
{
    rotate_string(this->smile->cipher_alpha, 13);
}

RCipher ::~RCipher() {}
// -------------------------------------------------------
