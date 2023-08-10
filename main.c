/* ALAT (Advanced Linear Algebra Toolkit) 

ALAT project was developed for calculating linear algebratic 
problems automatically. Especially, in engineering and science,
linear algebratic problems are so hot topic. So, I've decided to
write this project. I've seperated this project into 4 parts
mainly. First is 'matrices.h' file which contains the methods
related to matrix operations. Second is 'vectors.h' file which 
contain the methods about vector operations. Third is 'apps.h' 
file which contain the common applications related with linear 
algebra. Fourth is 'crypts.h' file which provide the cryptography 
operations.

Of course, I may have made mistake in some methods. Please, 
contact the with me over my e-mail address.

Resource: Elementary Linear Algebra, Sixth Edition by Ron LARSON, 
David C. FALVO

*/

#define AUTHOR   "Can Gulmez"
#define EMAIL    "ahmetcangulmez02gmail.com"
#define VERSION  "1.0.0"
#define RESOURCE "Elementary Linear Algebra, \
                  Sixth Edition by\
                  Ron Larson, David C. FALVO"

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
// #include "matrices.h"
// #include "vectors.h"
// #include "apps.h"
// #include "crypts.h"

/* Can be used this method for displaying any matrix. */
void _display_matrix_(int row, int col, float matrix[row][col]) {
   // Iterate the 'matrix' and then display all elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
         printf("%f ", matrix[i][j]); }
      // Put the new line at the end of each row. 
      printf("\n"); }
}

int main(void) {



   return 0;
}
