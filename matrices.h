/* Matrix operations in ALAT (Advanced Linear Algebra Toolkit) 

Matrix is defined as the 2D arrays. Especially, in engineering and
math, so many problems requires working with matrix operations and 
rules. But matrix operations can be so ashausting and complex 
manually. So I've decided to write this source file which contains
a tons of basics and advanced methods. I hope, it will be useful...

+ Basics Methods:
   - diagonal()
   - ishomogen()
   - iszeros()
   - isones()
   - isidentity()
   - zeros()
   - ones()
   - identity()
   - arbitrary()
   - sequential()
   - randint()
   - isequal()
   - highest()
   - lowest()
   - agg0()
   - agg1()
   - transpose()
   - islowertri()
   - isuppertri()
   - istriangle()
   - mean()
   - sort()
   - stdev()
   - mode()
   - median()
   - shuffle()
   - reshape()
   - concat0()
   - concat1()
   - add()
   - subtract()
   - scaler_mul()
   - dot_mul()
   - cross_mul()
   - scaler_div()

+ Advanced Method:
   - det()
   - minors()
   - cofactors()
   - isinvertable()
   - adjoint()
   - inverse()
   - cross_div()
   - solve()
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* ------------------------ Helper Methods ----------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

/* Convert given 'matrix' to 'array'. */
void _to_array_(int row, int col, float matrix[row][col], 
                float array[row * col]) {
   int index = 0; // array index
   // Iterates the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   array[index] = matrix[i][j]; index ++; }}
}

/* Convert given 'array' to 'matrix'. */
void _to_matrix_(int row, int col, float array[row * col], 
                 float matrix[row][col]) {
   int index = 0; // array index
   // Iterates the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   matrix[i][j] = array[index]; index ++; }}
}

/* Return True, if 'item' is in 'string'. */
bool _is_in_(char item, char *string) {
   int in = 0; // if 'item' is in 'string', increase it
   int len = strlen(string); // get length of 'string'
   // Iterate the 'string' chars.
   for (int i=0; i<len; i++) if (string[i] == item) in ++;
   if (in != 0) return true; else return false;
}

/* Get index of 'item' in related 'string'. */
int _get_index_(char item, char *string) {
   int index = 0; 
   int len = strlen(string); // lenght of 'string'
   for (int i=0; i<len; i++) // iterate the 'string' chars
   { if (item == string[i]) break; index ++; }
   return index;
}

/* Determine if a item is in 'array' or not. */
bool _is_exist_(int item, int lenght, int array[lenght]) {
   // Find existing item.
   int exists = 0;
   // Iterate the 'array'.
   for (int i=0; i<lenght; i++) if (array[i] == item) exists ++;
   if (exists != 0) return true;
   else return false;
}

/* Determine if a item is in 'array' or not. */
bool _is_exist_f_(float item, int lenght, float array[lenght]) {
   // Find existing item.
   int exists = 0;
   // Iterate the 'array'.
   for (int i=0; i<lenght; i++) if (array[i] == item) exists ++;
   if (exists != 0) return true;
   else return false;
}

/* Generate the random indexes. */
void _generate_indexes_(int row, int col, int array[row*col]) {
   // Adjust time seed.
   time_t unique = time(NULL); srand(unique);
   int start = 0;
   // Generate the index.
   while (true) {
      int index = rand() % (row * col) + 1;
      // Use '_is_exist_' method.
      if (!_is_exist_(index, row*col, array)) {
         // Append unique index onto 'array'.
         array[start] = index; start ++;
      }
      // Break up the loop. 
      if (start == row*col) break;
   }
}

/* Copy the 'matrix' into different matrix. */
void _copy_matrix_(int row, int col, float matrix[row][col], 
                    float result[row][col]) {
   // Iterate the 'matrix' and copy the elements into 'result'.
   for (int i=0; i<row; i++) {for (int j=0; j<col; j++) {
   result[i][j] = matrix[i][j]; }}
}

/* Delete the row of any matrix. */
void _del_row_(int index, int row, int col, float matrix[row][col],
               float result[row-1][col]) {
   int start = 0;
   // Iterate the 'matrix' until it will reach 'index'.
   for (int i=0; i<index; i++) { for (int j=0; j<col; j++) {
   result[start][j] = matrix[i][j]; } start ++; }
   // Iterate the 'matrix' from 'index' to 'row'.
   for (int i=index+1; i<row; i++) { for (int j=0; j<col; j++) {
   result[start][j] = matrix[i][j]; } start ++; }
}

/* Switch the two rows for vanishing zero element/s. */
void _switch_rows_(int row, int col, float matrix[row][col], 
                   int index) {
   // Find the proper row that will be switched with 'index'.
   int nonzerorow; 
   for (int i=0+index; i<col; i++) if (matrix[i][index] != 0.0)
         { nonzerorow = i; break; }
   // Create the arrays which contain 'index' and 'nonzerorow'.
   float array1[1][col]; float array2[1][col];
   // Fill the arrays with the proper rows of 'matrix'.
   for (int j=0; j<col; j++) array1[0][j] = matrix[index][j];
   for (int j=0; j<col; j++) array2[0][j] = matrix[nonzerorow][j];
   // And replace the 'array1' and 'array2' onto 'matrix'.
   for (int j=0; j<col; j++) matrix[index][j] = array2[0][j];
   for (int j=0; j<col; j++) matrix[nonzerorow][j] = array1[0][j];
   // Lastly, multiply the 'matrix' by -1.
   // for (int i=0; i<row; i++)
   //    for (int j=0; j<col; j++)
   //       if (matrix[i][j] != 0.0)
   //          matrix[i][j] = -1 * matrix[i][j];
} 

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* ----------------------- Basics Methods ----------------------- */
/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */

/* If matrix is square, extract the diagonal of matrix. */
void diagonal(int row, int col, float matrix[row][col], 
              float result[1][col]) {
   // Check if 'matrix' parameter is square or not.
   if (row != col) { 
      puts("MatrixError: 'matrix' must be square."); exit(1);
   // Append the diagonal elements onto 'result' parameter.
   } else for (int i=0; i<row; i++) result[0][i] = matrix[i][i];
}
 
/* Return true, if 'matrix' is homogenous. */
bool ishomogen(int row, int col, float matrix[row][col]) {
   int homogen = 0;
   // Iterate the 'matrix'.
   for (int i=0; i<row; i++) if (matrix[i][col-1] == 0) homogen ++;
   if (homogen == col) return true; else return false;
}

/* Return true, if 'matrix' contains just 0s. */
bool iszeros(int row, int col, float matrix[row][col]) {
   int zeros = 0;
   // Iterate the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   if (matrix[i][j] == 0) zeros ++; } }
   // Determine 'matrix' is the zero matrix.
   if (zeros == row * col) return true; else return false;
}

/* Return true, if 'matrix' contains just 1s. */
bool isones(int row, int col, float matrix[row][col]) {
   int ones = 0;
   // Iterate the 'matrix'.
   for (int i=0; i<row; i++) 
      for (int j=0; j<col; j++)
         if (matrix[i][j] == 1) ones ++; 
   // Determine 'matrix' is the one matrix.
   if (ones == row * col) return true; else return false;
}

/* Return true, 'matrix' is identity. */
bool isidentity(int row, int col, float matrix[row][col]) {
   int zeros = 0; int ones = 0; float diag[1][col];
   // Get the diagonal matrix.
   diagonal(row, col, matrix, diag);
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      if (matrix[i][j] == 0) zeros ++; 
      if (matrix[i][j] == 1) ones ++; } }
   // Check if 'matrix' is identity or not.
   if (zeros + ones == row * col && \
       isones(1, col, diag) == 1 && \
       ones == col) return true;
   else return false; 
}

/* Generate new matrix that just contains 0s. */
void zeros(int row, int col, float result[row][col]) {
   // New 0s matrix.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = 0; } }
}

/* Generate new matrix that just contains 1s. */
void ones(int row, int col, float result[row][col]) {
   // New 1s matrix.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = 1; } }
}

/* Generate new matrix that is identity. */
void identity(int row, int col, float result[row][col]) {
   // New identity matrix.
   if (row != col) {
      puts("MatrixError: 'matrix' must be square."); exit(1);
   } else {
      // Previously, create the zeros matrix.
      zeros(row, col, result);
      // And then, append 1s onto diagonal of 'result'.
      for (int i=0; i<row; i++) result[i][i] = 1;
   }
}

/* Generate new matrix that is arbitrary. */
void arbitrary(float value, int row, int col, 
               float result[row][col]) {
   // New arbitrary matrix.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) { 
   result[i][j] = value; }}
}

/* Generate the sequential matrix. */
void sequential(float initial, float end, int row, int col, 
                float result[row][col]) {

   float step; // step interval
   // Determine the step interval for two situations.
   if (end - initial > 0) 
   step = (float) (end-initial)/(float) (row*col-1);
   else step = (float) (end-initial) / (float) (row*col-1);
   float total = initial;
   // Iterate the 'result' matrix and replace the elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = total; total += step; }}
}

/* Generate new matrix that contains just random integer. */
void randint(int initial, int end, int row, int col, 
             float result[row][col]) {
   // Previously, adjust seed to random with 'time.h' library.
   srand(time(NULL)); int integer;
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) { 
   while (true) {
      // Generate the random integer.
      integer = rand() % (end + 1);
      if (integer >= initial) break;
   }
   // Append the random integer onto 'result' matrix.
   result[i][j] = (float) integer; }} 
}

/* Return true, if given two matrix are equals for each other. */
bool isequal(int row, int col, float matrix1[row][col], 
             float matrix2[row][col]) {
   // Count the same elements.
   int equal = 0;
   // Iterate both two the matrices.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) { 
   if (matrix1[i][j] == matrix2[i][j]) equal ++; }}
   // Check if given two matrix are equals or not.
   if (equal == row * col) return true; else return false;
}

/* Return the highest element in matrix. */
float highest(int row, int col, float matrix[row][col]) {
   // Highest element.
   float high = 0;
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      if (matrix[i][j] >= high) high = matrix[i][j]; 
   }}
   return high;
}

/* Return the lowest element in matrix. */
float lowest(int row, int col, float matrix[row][col]) {
   // Lowest element.
   float low = 0;
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      if (matrix[i][j] <= low) low = matrix[i][j]; 
   }}
   return low; 
}

/* Aggregate the matrix rows as horizontal.  */
void agg0(int row, int col, float matrix[row][col], 
          float result[1][col]) {
   float total = 0;
   // Iterates the 'matrix'.
   for (int j=0; j<col; j++) { for (int i=0; i<row; i++) { 
   // sum each column into 'total'
   total += matrix[i][j]; } 
   // and in each iteration, insert the total into 'result'.
   result[0][j] = total; total = 0; }
}

/* Aggregate the matrix rows as vertical.  */
void agg1(int row, int col, float matrix[row][col], 
                float result[row][1]) {
   float total = 0;
   // Iterates the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) { 
   // sum each row into 'total'
   total += matrix[i][j]; } 
   // and in each iteration, insert the total into 'result'.
   result[i][0] = total; total = 0; }
}

/* Get the transpose of 'matrix' elements. */
void transpose(int row, int col, float matrix[row][col], 
                 float result[col][row]) {
   // Iterate the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[j][i] = matrix[i][j]; }}
}

/* Return true, if 'matrix' is lower triangular. */
bool islowertri(int row, int col, float matrix[row][col]) {
   // Count the same elements.
   int issame = 0;
   // Append the upper triangular elements.
   int index = 0; float ltri[row];
   // Iterate the 'matrix' elements.
   for (int i=0; i<row-1; i++) { for (int j=i+1; j<col; j++) {
   ltri[index] = matrix[i][j]; index ++; }}
   // Generate the zeros matrix.
   float zero[1][index]; zeros(1, index, zero);
   // Compare the 'zero' and 'ltri' elements.
   for (int j=0; j<index; j++) 
   if (zero[0][j] == 0 && ltri[j] == 0) issame ++;

   if (issame == index && row == col) return true;
   else return false;
}

/* Return true, if 'matrix' is upper triangular. */
bool isuppertri(int row, int col, float matrix[row][col]) {
   // Get the transpose of 'matrix'.
   float matrix2[col][row]; 
   transpose(row, col, matrix, matrix2);
   // Can be used 'isltri' method in here.
   if (islowertri(col, row, matrix2)) return true;
   else return false;
}

/* Return true, if 'matrix' is upper or lower triangular. */
bool istriangle(int row, int col, float matrix[row][col]) {
   // Can be used both 'islowertri' and 'isuppertri' methods.
   if (islowertri(row, col, matrix) || 
      isuppertri(row, col, matrix)) 
      return true; else return false;
}

/* Get mean of 'matrix'. */
float mean(int row, int col, float matrix[row][col]) {
   // Sum the all elements of given 'matrix'.
   float total = 0;
   // Iterate the matrix.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      total += matrix[i][j];
   }}
   return total / (row * col);
}

/* Sort the all elements of 'matrix' by ascending or descending. */
void sort(char method, int row, int col, float matrix[row][col], 
          float result[row][col]) {
   int temp = 0;
   // Convert the 'matrix' to 'array'.
   float array[row * col];
   _to_array_(row, col, matrix, array);
   // Sort the elementsin the 'array' according to 'method'.
   for (int i=0; i<row*col; i++) { for (int j=i+1; j<row*col; j++){
      // Sor the elements in ascending order.
      if (method == 'A' || method == 'a') { 
         if (array[i] > array[j]) { temp = array[i]; 
         array[i] = array[j]; array[j] = temp; }}
      // Sort the elements in descending order.
      else if  (method == 'D' || method == 'd') { 
               if (array[i] < array[j]) { temp = array[i]; 
               array[i] = array[j]; array[j] = temp; }}
      // Otherwise return the error.
      else {
         char* error1 = "MatrixError: 'method' parameter must be ";
         char* error2 = "'A', 'a' for ascending order or 'D', 'd'";
         char* error3 = " for descending order";
         printf("%s%s%s.\n", error1, error2, error3);
         exit(EXIT_FAILURE); }}}
   // Lastly, convert the ordered 'array' to 'matrix'.
   _to_matrix_(row, col, array, result);
}
 
/* Calculate the standard deviation of 'matrix'. */
float stdev(int row, int col, float matrix[row][col]) {
   // Calculate the mean.
   float m = mean(row, col, matrix);
   float pows = 0;
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      // Get the pows of iteration.
      float _abs = m - matrix[i][j];
      if (_abs < 0) pows += pow(-1 * _abs, 2); 
      else pows += pow(_abs, 2); 
   }}
   // Calculate the standard deviation and return that.
   return sqrt(pows / (row * col));
}

/* Find the median of 'matrix'. */
float median(int row, int col, float matrix[row][col]) {
   // Sort the all elements of 'matrix'.
   float sorted[row][col]; sort('a', row, col, matrix, sorted);
   // Convert the 'sorted' into array.
   float array[row * col]; _to_array_(row, col, sorted, array);
   // Find the median of 'array'.
   if ((row * col) % 2 == 1) return array[(int) (row * col / 2)];
   else {
      int first = (int) (row * col / 2) - 1;
      int second = (int) (row * col / 2);
      return (array[first] + array[second]) / 2;
   }
}

/* Shuffle the 'matrix' elements. */
void shuffle(int row, int col, float matrix[row][col], 
         float result[row][col]) {
   // Generate the random indexes.
   int array[row * col]; _generate_indexes_(row, col, array);
   // Convert the 'matrix' into array.
   float array2[row * col]; _to_array_(row, col,  matrix, array2);
   // Iterate the 'matrix'.
   int start = 0; // Fill in the 'result' matrix.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = array2[array[start]-1]; start ++; }} 
}

/* Reshape the 'matrix' elements. */
void reshape(int row1, int col1, float matrix[row1][col1], 
             int row2, int col2, float result[row2][col2]) {
   // Start index for 'result' matrix.
   int start = 0;
   // Check if rows and cols of each two 'matrix1' and 'result'
   // are equals, else return an error message.
   if (row1 * col1 != row2 * col2) {
      puts("MatrixError: Found dimension discrepancy.");
      exit(EXIT_FAILURE);
   }
   // Convert the 'matrix1' into array.
   float array[row1 * col1]; _to_array_(row1, col1, matrix, array);
   // Iterate the 'result' matrix.
   for (int i=0; i<row2; i++) { for (int j=0; j<col2; j++) {
   result[i][j] = array[start]; start ++; }}
}

/* Concatenate the 'matrix1' and 'matrix2' as horizontal. */
void concat0(int row1, int col1, float matrix1[row1][col1], 
             int row2, int col2, float matrix2[row2][col2], 
             float result[row1 + row2][col1]) {
   // Check if given two matrices are proper or not.
   if (col1 != col2) {
      puts("MatrixError: Found dimension dicrepancy.");
      exit(EXIT_FAILURE);
   }
   // Iterate the 'matrix1'.
   for (int i=0; i<row1; i++) { for (int j=0; j<col1; j++) {
   result[i][j] = matrix1[i][j]; }}
   // Iterate the 'matrix2'.
   for (int i=0; i<row2; i++) { for (int j=0; j<col2; j++){
   result[i+row1][j] = matrix2[i][j]; }}
}

/* Concatenate the 'matrix1' and 'matrix2' as vertical. */
void concat1(int row1, int col1, float matrix1[row1][col1], 
             int row2, int col2, float matrix2[row2][col2], 
             float result[row1][col1 + col2]) {
   // Check if given two matrices are proper or not.
   if (row1 != row2) {
      puts("MatrixError: Found dimension discrepancy.");
      exit(EXIT_FAILURE);
   }
   // Iterate the 'matrix1'.
   for (int i=0; i<row1; i++) { for (int j=0; j<col1; j++) {
   result[i][j] = matrix1[i][j]; }}
   // Iterate the 'matrix2'.
   for (int i=0; i<row2; i++) { for (int j=0; j<col2; j++){
   result[i][j+col1] = matrix2[i][j]; }}
}

/* Add the 'matrix1' and 'matrix2' elements. */
void add(int row, int col, float matrix1[row][col], 
         float matrix2[row][col], float result[row][col]) {
   // Iterate the 'matrix1' and 'matrix2'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix1[i][j] + matrix2[i][j]; }}
}

/* Subtract the 'matrix1' from 'matrix2' elements. */
void subtract(int row, int col, float matrix1[row][col], 
              float matrix2[row][col], float result[row][col]) {
   // Iterate the 'matrix1' and 'matrix2'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix1[i][j] - matrix2[i][j]; }}
}

/* Multiplies 'scaler' and 'matrix' elements. */
void scaler_mul(float scaler, int row, int col, 
                float matrix[row][col], float result[row][col]) {
   // Iterate the 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix[i][j] * scaler; }}
}


/* Multiplies the 'matrix1' and 'matrix2' elements as dot. */
void dot_mul(int row, int col, float matrix1[row][col], 
             float matrix2[row][col], float result[row][col]) {
   // Iterate the 'matrix1' and 'matrix2'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix1[i][j] * matrix2[i][j]; }}
}

/* Multiplies the 'matrix1' and 'matrix2' as cross. */
void cross_mul(int row1, int col1, float matrix1[row1][col1], 
             int row2, int col2, float matrix2[row2][col2], 
             float result[row1][col2]) {

   // These variable is necassery when multiplies elements.
   float total = 0;
   int index = col1;
   // Check if given two matrices are proper or not.
   if (col1 != row2) {
      puts("MatrixError: Found dimension discrepancy."); 
      exit(EXIT_FAILURE);
   }
   // Get transpose of 'matrix2'.
   float transposed[col2][row2];
   transpose(row2, col2, matrix2, transposed);
   // Save the results in here.
   int start = 0; float array[row1*col2]; 

   // Iterate the 'matrix1' and 'matrix2'.
   for (int i=0; i<row1; i++) {       
      for (int j=0; j<col2; j++) {    
         for (int k=0; k<row2; k++) { 
            // Multiplies elements of each matrices.
            float value = matrix1[i][k] * transposed[j][k];
            total += value; index --;
            // Save the results onto 'result' matrix.
            if (index == 0) {
            array[start] = total; 
            total = 0; index = col1; start ++;}
   }}}
   // Fill in the 'result' matrix.
   _to_matrix_(row1, col2, array, result);
}

/* Divides the 'scaler' to 'matrix'. */
void scaler_div(float scaler, int row, int col, 
                float matrix[row][col], float result[row][col]) {
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix[i][j] / scaler; }}
}

/* Divides the 'matrix1' to 'matrix2'. */
void dot_div(int row, int col, float matrix1[row][col], 
             float matrix2[row][col], float result[row][col]) {
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
   result[i][j] = matrix1[i][j] / matrix2[i][j]; }}
}

/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */
/* --------------------- Advanced Methods ----------------------- */
/* -------------------------------------------------------------- */
/* -------------------------------------------------------------- */

/* Calculate the determinant of any square matrix. */
float det(int row, int col, float matrix[row][col]) {
   // Check if 'matrix' is square or not.
   if (row != col) {
      puts("MatrixError: 'matrix' must be square.");
      exit(EXIT_FAILURE);
   }
   // Calculate the determinant of 1x1 matrix.
   if (row == 1) return matrix[0][0];
   // Calculate the determinant of 2x2 matrix.
   if (row == 2) {
      // Multiply the diagonals and get the difference.
      float s1 = matrix[0][0] * matrix[1][1];
      float s2 = matrix[0][1] * matrix[1][0];
      return s1 - s2;
   }
   // Calculate the determinant of 3x3 and more matrix.
   if (row >= 3) {
      // The main strategy is that 'matrix' will be converted
      // upper triangular form. And then multiply the elements
      // in which main diagonal of upper triangular matrix.
      float uppertri[row][col];
      // Copy the 'matrix' into 'uppertri' for converting.
      _copy_matrix_(row, col, matrix, uppertri);
      // Control the iteration number with 'k' variable.
      int k = 0;
      // Count the switching row operations.
      int switching = 0; 
      // Step by step, generate the upper triangular matrix.
      while (true) {
         // Iterate the all elements of 'matrix'.
         for (int i=1+k; i<row; i++) {
            // Generally, these sub-matrices will be generated.
            float m1[1][col]; float m2[1][col]; float m3[1][col];
            float m4[1][col];
            // In some cases, this algorithm will raise the error.
            // Because if element in main diagoal is zero, during
            // division operation, 'coef' will be 'nan'. To fix
            // this, can be used additional methods.
            if (uppertri[k][k] == 0.0) {
               // Switch the 'k'. row with next row.
               _switch_rows_(row, col, uppertri, k);
               // While calculating determinant, if the two rows
               // switch with each other, in cases, determinant
               // is multiplied by -1.
               switching ++;
            }
            // Apart from that, continue generating the matrix.
            float coef = -1 * uppertri[i][k] / uppertri[k][k];
            // Generate the sub-matrices and fill in it.
            for (int j=0; j<col; j++) m1[0][j] = uppertri[k][j];
            for (int j=0; j<col; j++) m2[0][j] = uppertri[i][j];
            // Multiply the 'm2' matrix with 'coef'.
            scaler_mul(coef, 1, col, m1, m3);
            // Add up the 'm2' matrix and 'm3' matrix.
            add(1, col, m2, m3, m4);
            // Replace the old row with new 'm4' row.
            for (int j=0; j<col; j++) uppertri[i][j] = m4[0][j];
         }
         // Update the control variable in each iteration.
         k ++;
         // Break up the loop if necassary condition are provided.
         if (k == row) break;
      }
      // To get the determinant of 'matrix', it's enough to 
      float det = 1.0;
      // multiply the main diagonal elements of 'uppertri' matrix.
      for (int i=0; i<row; i++) det *= uppertri[i][i];

      return det * pow(-1, switching);
   }
}

/* Extract the minors map of 'matrix'. */
void minors(int row, int col, float matrix[row][col], 
            float result[row][col]) {
   // Check if given 'matrix' is proper for this method.
   if (col == 1 || row == 1) {
      puts("MatrixError: 1x1 matrix is unexceptable.");
      exit(EXIT_FAILURE);
   }
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      // Copy the 'matrix' in here. 
      float copied[row][col]; 
      _copy_matrix_(row, col, matrix, copied); 
      // Parse just the 'matrix' according to first row.
      float parsed[row-1][col]; 
      _del_row_(i, row, col, copied, parsed);
      // Get the transpose of 'deleted'.
      float transposed[col][row-1]; 
      transpose(row-1, col, parsed, transposed);
      // Delete the again first row of 'transposed'.
      float parsed2[col-1][row-1];
      _del_row_(j, col, row-1, transposed, parsed2);
      // Again transposed the 'deleted2' matrix.
      float transposed2[row-1][col-1];
      transpose(col-1, row-1, parsed2, transposed2);
      // Calculate the determinant of reduced 'matrix' and 
      // then replace it into 'result' matrix.
      result[i][j] = det(row-1, col-1, transposed2); }}
}

/* Extract the cofactors map of 'matrix'. */
void cofactors(int row, int col, float matrix[row][col], 
               float result[row][col]) {
   // Check if given 'matrix' is proper for this method.
   if (col == 1 || row == 1) {
      puts("MatrixError: 2x2 matrix is unexceptable.");
      exit(EXIT_FAILURE);
   }
   // Extract the minors map of 'matrix'.
   minors(row, col, matrix, result);
   // Multiply the element which is the odd of 
   // sum of indexes by -1.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      if ((i+j)%2 == 1 && result[i][j] != 0.0)            
         result[i][j] = -1 * result[i][j];                
   }}                                                      
}

/* Return true, if 'matrix' is invertible. */
bool isinvertible(int row, int col, float matrix[row][col]) {
   // Calculate the determinant of 'matrix'.
   float determinant = det(row, col, matrix);
   if (determinant != 0) return true; else return false;
}

/* Calculate the adjoint of 'matrix'.*/
void adjoint(int row, int col, float matrix[row][col], 
            float result[row][col]) {
   // Extract the cofactors map into 'cofactor'.
   float cofactor[row][col]; 
   cofactors(row, col, matrix, cofactor);
   // Get transpose of 'cofactor' into 'result'.
   transpose(row, col, cofactor, result);
}

/* Calculate the inverse of 'matrix'. */
void inverse(int row, int col, float matrix[row][col], 
             float result[row][col]) {
   // Check if 'matrix' is invertible or not.
   if (isinvertible(row, col, matrix) == false) {
      puts("MatrixError: 'matrix' is not invertible.");
      exit(EXIT_FAILURE);
   }
   // Calculate the determinant of 'matrix'.
   float determinant = det(row, col, matrix);
   // Extract the adjoint of 'matrix'.
   float adj[row][col]; adjoint(row, col, matrix, adj);
   // Calculate the inverse with 'scaler_div' method.
   scaler_div(determinant, row, col, adj, result);
}

/* Divide the 'matrix1' to 'matrix2' as cross */
void cross_div(int row, int col, float matrix1[row][col], 
               float matrix2[row][col], float result[row][col]){
   // Check if 'matrix2' is invertible or not.
   if (isinvertible(row, col, matrix2) == false) {
      puts("MatrixError: 'matrix2' is invertible.");
      exit(EXIT_FAILURE);
   }
   // Get inverse of 'matrix2'.
   float inv[row][col]; inverse(row, col, matrix2, inv);
   // Multiply the 'matrix1' and 'inv' as cross.
   cross_mul(row, col, matrix1, row, col, inv, result);
}
 
/* Solve a augmented matrix. */
void solve(int row, int col, float matrix[row][col], 
           float result[row][1]) {
   // Check if 'matrix' is proper form for solving equations.
   if (col - row != 1) {
      puts("MatrixError: 'matrix' must have augmented form.");
      exit(EXIT_FAILURE);
   }
   // Extract the main square and target matrices.
   float smatrix[row][col-1]; 
   float target[row][1];
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) for (int j=0; j<col-1; j++) 
      smatrix[i][j] = matrix[i][j]; 
   for (int i=0; i<row; i++) target[i][0] = matrix[i][col-1];
   // Check if the 'smatrix' is invertible or not.
   if (isinvertible(row, col-1, smatrix) == false) {
      puts("MatrixError: 'smatrix' is not invertible.");
      exit(EXIT_FAILURE);
   }
   // Get inverse or 'smatrix'.
   float inv[row][col-1]; inverse(row, col-1, smatrix, inv);
   // Multiply the 'inv' and 'target' matrices as cross.
   cross_mul(row, col-1, inv, row, 1, target, result);
}

