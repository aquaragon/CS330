#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;



/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class

struct Cipher::CipherCheshire {
    string cipher_alpha;
};

class CCipher : public Cipher
{
public:
   CCipher();
   CCipher(int positive_shift);
   virtual ~CCipher();
};

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

