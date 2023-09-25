/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) 

Methods: 
   to_matrix(), encode(), decode(), to_message()
*/

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matrices.h"

/* Consistent chararacters */
#define CRYPT "\
0123456789\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz\
é!'^+$%&/\\(){}[]=*-?-_~;,`.: <>|\"@\
"  

/* --------------------------------------------------------------- */
/* ------------------------ Basics Methods ----------------------- */
/* --------------------------------------------------------------- */

/* Convert the 'msg' to square 'matrix'. If dimension of 'matrix' 
is not enough, and then raise error. If there are missing elements
in 'matrix', and then put -1.0 in blank spaces. For example: 

double matrix[6][6];
char *message = "Belief creates the actual facts.";
to_matrix(message, 6, 6, matrix);
display_matrix(6, 6, matrix);

11.000000 40.000000 47.000000 44.000000 40.000000 41.000000 
89.000000 38.000000 53.000000 40.000000 36.000000 55.000000 
40.000000 54.000000 89.000000 55.000000 43.000000 40.000000 
89.000000 36.000000 38.000000 55.000000 56.000000 36.000000 
47.000000 89.000000 41.000000 36.000000 38.000000 55.000000 
54.000000 87.000000 -1.000000 -1.000000 -1.000000 -1.000000
*/
void to_matrix(char* msg, int row, int col, double result[row][col]){
   // Check if 'matrix' has enough dimension.
   assert (row * col >= strlen(msg));
   // Check if the 'matrix' is square or not.
   assert (row == col);
   // Count the total consistent characters in 'msg'.
   int total = 0;
   for (int i=0; i<strlen(CRYPT); i++) 
      for (int j=0; j<strlen(msg); j++)
         if (msg[j] == CRYPT[i]) total ++;
   // Check the all characters of 'msg' is in 'CRYPT'.
   assert (total == strlen(msg));
   // Create a 'array' and then fill it with integers 
   // corresponding to characters of 'msg' from the 'CRYPT'.
   int array[strlen(msg)]; int index = 0; 
   // Iterate the both 'CRYPT' and 'msg' characters.
   for (int i=0; i<strlen(msg); i++) { 
      for (int j=0; j<strlen(CRYPT); j++) { 
         if (msg[i] == CRYPT[j]) break; else index ++;}
      // Upload the corresponding integers to 'array'.
      array[i] = index; index = 0;
   }
   // Save the elements of 'array' into 'result'. If there are       
   // missing elements of 'array', fill with -1.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) {
      if (index >= strlen(msg)) result[i][j] = -1.0;
      else result[i][j] = (double) array[index];
      index ++;
   }
}

/* Encode the 'msg' with 'encoding' matrix. 'encoding' matrix must
be invertible. Because, to enocde message we need it. For example:

char *message = "Belief creates the actual facts.";
double encoding[6][6] = {
   {1, 0, 1, 4, 0, 1}, 
   {0, 0, 2, -2, 0, 0}, 
   {5, 1, 0, 2, 0, 3}, 
   {1, 2, 1, 0, 2, 0}, 
   {2, 2, 0, -1, 5, 8}, 
   {0, -3, 1, 8, 3, 0}, 
};
double encoded[6][6];
encode(message, 6, 6, encoding, encoded);
display_matrix(6, 6, encoded);

370.000000 92.000000 176.000000 346.000000 411.000000 472.000000 
466.000000 40.000000 260.000000 790.000000 425.000000 536.000000 
626.000000 165.000000 243.000000 507.000000 445.000000 651.000000 
446.000000 152.000000 252.000000 592.000000 498.000000 651.000000 
364.000000 24.000000 316.000000 494.000000 427.000000 474.000000 
46.000000 -2.000000 226.000000 33.000000 -10.000000 43.000000
*/
void encode(char* msg, int row, int col, double encoding[row][col], 
            double result[row][col]) {
   // Check if the 'encoding' is square or not.
   assert (row == col);
   // Check if 'encoding' matrix is invertible or not.
   assert (isinvertible(row, col, encoding));
   // Convert the 'message' into matrix.
   double matrix[row][col]; 
   to_matrix(msg, row, col, matrix);
   // Finally, multiply 'matrix' and 'encoding' as cross.
   cross_mul(row, col, matrix, row, col, encoding, result);
}

/* Decode the 'encoded' matrix with 'encoding' matrix. For 
example: 

double encoded[6][6] = {
   {370, 92, 176, 346, 411, 472},  
   {466, 40, 260, 790, 425, 536},
   {626, 165, 243, 507, 445, 651}, 
   {446, 152, 252, 592, 498, 651},
   {364, 24, 316, 494, 427, 474},
   {46, -2, 226, 33, -10, 43},
};
double encoding[6][6] = {
   {1, 0, 1, 4, 0, 1}, 
   {0, 0, 2, -2, 0, 0}, 
   {5, 1, 0, 2, 0, 3}, 
   {1, 2, 1, 0, 2, 0}, 
   {2, 2, 0, -1, 5, 8}, 
   {0, -3, 1, 8, 3, 0}, 
};
double decoded[6][6];
decode(6, 6, encoded, encoding, decoded);
display_matrix(6, 6, decoded);

11.000000 40.000000 47.000000 44.000000 40.000000 41.000000 
89.000000 38.000000 53.000000 40.000000 36.000000 55.000000 
40.000000 54.000000 89.000000 55.000000 43.000000 40.000000 
89.000000 36.000000 38.000000 55.000000 56.000000 36.000000 
47.000000 89.000000 41.000000 36.000000 38.000000 55.000000 
54.000000 87.000000 -1.000000 -1.000000 -1.000000 -1.000000
*/
void decode(int row, int col, double encoding[row][col], 
            double encoded[row][col], double result[row][col]){
   // Check if 'encoding' matrix is invertible or not.
   assert (isinvertible(row, col, encoding));
   // Calculate the inverse of 'encoding' matrix.
   double inversed[row][col]; 
   inverse(row, col, encoding, inversed);
   // Multiply the 'encoded' and 'inversed' matrix.
   cross_mul(row, col, encoded, row, col, inversed, result);
   // Lastly, round the all elements of 'result' for ensure.
}

/* Convert 'encoded' matrix to message. For example: 

double encoded[6][6] = {
   {370, 92, 176, 346, 411, 472},  
   {466, 40, 260, 790, 425, 536},
   {626, 165, 243, 507, 445, 651}, 
   {446, 152, 252, 592, 498, 651},
   {364, 24, 316, 494, 427, 474},
   {46, -2, 226, 33, -10, 43},
};
double encoding[6][6] = {
   {1, 0, 1, 4, 0, 1}, 
   {0, 0, 2, -2, 0, 0}, 
   {5, 1, 0, 2, 0, 3}, 
   {1, 2, 1, 0, 2, 0}, 
   {2, 2, 0, -1, 5, 8}, 
   {0, -3, 1, 8, 3, 0}, 
};
char* msg = to_message(6, 6, encoded, encoding);
puts(msg);

Belief creates the actual facts.
*/
char* to_message(int row, int col, double encoding[row][col], 
                 double encoded[row][col]) {
   // Use the heap memory for dynamic memory allocation.
   char* msg = (char*) malloc(row * col * sizeof(char));
   int index = 0;
   // Previously decode 'encoded' matrix.
   double decoded[row][col]; 
   decode(row, col, encoding, encoded, decoded);
   // Convert the data type of 'decode' to integer.
   // Find the characters corresponding to 'decoded' elements.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      if (decoded[i][j] != -1.0) 
         msg[index] = CRYPT[(int) (float) decoded[i][j]], 
         index ++;

   return msg; 
}
