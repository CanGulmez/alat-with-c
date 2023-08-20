/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) 

Cryptography is a special area of linear algebra. Especially, in 
intelligence and government jobs, cryptograpy is used to hide 
messages and transfer the message safely. So, in this source file, 
I put basics cryptography methods that give you some aspects. 
I hope, it will be useful...

+ to_matrix()
+ encode()
+ decode()
+ to_message()
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matrices.h"

// Global Values
// -------------

#define CRYPT "\
0123456789\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz\
!'^+$%&/\\(){}[]=*-?-_~;,`.:<>|\"@ \
"

/* Convert the 'message' to square 'matrix'. */
void to_matrix(char* msg, int row, int col, float result[row][col]){

   // Check if 'matrix' has enough dimension.
   if (strlen(msg) > row*col)  
      _raise_error_("CryptError", __FILE__,
                    "Insufficient matrix dimension.", __LINE__);
   // Check if the 'matrix' is square or not.
   if (row != col)  
      _raise_error_("CryptError", __FILE__,
                    "'row' and 'col' must be equal.", __LINE__);

   // Find the numbers according to chars.
   int index = 0; 
   float array[row * col]; 
   // Iterate the 'message' characters.
   for (int i=0; i<strlen(msg); i++) { 
      if (_is_in_(msg[i], CRYPT)) 
         array[index] = _get_index_(msg[i], CRYPT); 
      else _raise_error_("CryptError", __FILE__,
            "Found unidentified character/s.", __LINE__);
      index ++; 
   }
   index = 0;
   // If there are missing elements of 'array', fill in it.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      if (index >= strlen(msg)) result[i][j] = -1.0;
      else result[i][j] = array[index];
      index ++;
   }}
}

/* Encode just raw matrix with 'encoding' matrix. */
void encode(char* msg, int row, int col, float encoding[row][col], 
            float result[row][col]) {

   // Check if the 'ebcoding' is square or not.
   if (row != col)  
      _raise_error_("CryptError", __FILE__,
                    "'row' and 'col' must be equal.", __LINE__);
   // Check if 'encoding' matrix is invertible or not.
   if (isinvertible(row, col, encoding) == false) 
      _raise_error_("CryptError", __FILE__,
               "'encoding' matrix must be invertible.", __LINE__);

   // Convert the 'message' into matrix.
   float matrix[row][col]; to_matrix(msg, row, col, matrix);
   // Finally, multiply 'matrix' and 'encoding' as cross.
   cross_mul(row, col, matrix, row, col, encoding, result);
}

/* Decode the 'encoded' matrix with 'decoding' matrix. */
void decode(int row, int col, float encoded[row][col], 
            float encoding[row][col], float result[row][col]) {

   // Check if 'encoding' matrix is invertible or not.
   if (isinvertible(row, col, encoding) == false) 
      _raise_error_("CryptError", __FILE__,
         "'encoding' matrix must be invertible.", __LINE__);

   // Calculate the inverse of 'decoding' matrix.
   float inversed[row][col]; inverse(row, col, encoding, inversed);
   // Multiply the 'encoded' and 'inversed' matrix.
   cross_mul(row, col, encoded, row, col, inversed, result);

   // Lastly, round the all elements of 'result' for ensure.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = round(result[i][j]); }}
}

/* Convert 'decoded' matrix to message. */
char* to_message(int row, int col, float encoded[row][col], 
                 float encoding[row][col]) {

   int index = 0;
   char* message = (char*) calloc(row * col, sizeof(char));
   // Previously decode 'encoded' matrix.
   float decoded[row][col]; 
   decode(row, col, encoded, encoding, decoded);

   // Find the characters corresponding to 'decoded' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   if (decoded[i][j] != 0) 
      message[index] = CRYPT[ (int) decoded[i][j] ]; 
      index ++;
   }}
   return message; 
}
