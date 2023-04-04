#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
    smile = new CipherCheshire;
    smile->cipher_alpha = ALPHABET; 
}

/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
    if (is_valid_alpha(cipher_alpha))
    {
    smile = new CipherCheshire;  
    smile->cipher_alpha = cipher_alpha;
    }
    else
    {
   	cout << "Invalid alpha" << cipher_alpha << endl;
	exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
Cipher::~Cipher()
{
	delete smile;
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;
    int length = raw.length();
    int position;
    for (int i = 0; i < length; i++)
    {
	if (raw[i] == ' ')
        {
		retStr += ' ';
        }
	else
	{
		position = find_pos(ALPHABET, LOWER_CASE(raw[i]));
		if(isupper(raw[i]))
	        {
		    retStr += UPPER_CASE(smile->cipher_alpha[position]);
		}
		else
	        {
	            retStr += smile->cipher_alpha[position];
        	}
	}
    }
    
    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrypting...";
    int length = enc.length();
    int position;
    for (int i = 0; i < length; i++)
    {
	    if (enc[i] == ' ')
	    {
		    retStr += ' ';
	    }
	    else
            {
	   	 position = find_pos(smile->cipher_alpha, LOWER_CASE(enc[i]));
	   	 if(isupper(enc[i]))
	   	 {
	    	         retStr += UPPER_CASE(ALPHABET[position]);
	  	 }
	   	 else
	   	 {
	        	 retStr += ALPHABET[position];
	   	 }
	    }
    }


    cout << "Done" << endl;
    return retStr;

}
// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;

    while(alpha[pos] != c)
    {
	    pos++;
    }
    
    return pos;
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
