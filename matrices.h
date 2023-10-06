/* Matrix operations in ALAT (Advanced Linear Algebra Toolkit) 

+ Basics Methods:
   diagonal(), ishomogen(), iszeros(), isones(), isidentity(), 
   zeros(), ones(), identity(), arbitrary() sequential(), 
   randouble(), isequal(), highest(), lowest(), agg_hor()
   agg_ver(), transpose(), islowertri(), isuppertri()
   istriangle(), mean(), sort_asc(), sort_des(), stddev(), 
   mode(), median(), shuffle(), reshape(), concat_hor()
   concat_ver(), add(), subtract(), scaler_mul(), dot_mul()
   cross_mul(), scaler_div()

+ Advanced Method:
   uppertri(), det(), minors(), cofactors(), isinvertable(), 
   adjoint(), inverse(), lowertri(), solve()  
*/

/* Libraries */
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/* --------------------------------------------------------------- */
/* ------------------------ Helper Methods ----------------------- */
/* --------------------------------------------------------------- */

/* Convert 2D 'matrix' to 1D 'result'. */
void _to_array_(int row, int col, double matrix[row][col], 
                double array[row * col]) {
   // Append the all elements of 'matrix' into 'result'.
   int index = 0;
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      array[index] = matrix[i][j], index ++; 
}

/* Convert 1D 'array' to 2D 'result'. */
void _to_matrix_(int row, int col, double array[row * col], 
                 double matrix[row][col]) {
   // Put the all elements of 'array' into 'result'.
   int index = 0;
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      matrix[i][j] = array[index], index ++;
}

/* Copy the elements of 'matrix' to 'result'. */
void _copy_matrix_(int row, int col, double matrix[row][col],
                   double result[row][col]) {
   // Copy the elements of 'matrix'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = matrix[i][j];
}

/* Delete the row of 'matrix'. */
void _del_row_(int index, int row, int col, double matrix[row][col],
               double result[row-1][col]) {
   int start = 0;
   // Iterate the 'matrix' until it will reach 'index'.
   for (int i=0; i<index; i++) {
      for (int j=0; j<col; j++) 
         result[start][j] = matrix[i][j];  
      start ++; }
   // Iterate the 'matrix' from 'index' to 'row'.
   for (int i=index+1; i<row; i++) {
      for (int j=0; j<col; j++)
         result[start][j] = matrix[i][j];  
      start ++; }
}

/* Switch the two rows for vanishing zero element/s. */
void _switch_rows_(int row, int col, double matrix[row][col], 
                   int index) {
   // Find the proper row that will be switched with 'index'.
   int nonzerorow; 
   for (int i=0+index; i<col; i++) if (matrix[i][index] != 0.0)
         { nonzerorow = i; break; }
   // Create the arrays which contain 'index' and 'nonzerorow'.
   double array1[1][col]; double array2[1][col];
   // Fill the arrays with the proper rows of 'matrix'.
   for (int j=0; j<col; j++) array1[0][j] = matrix[index][j];
   for (int j=0; j<col; j++) array2[0][j] = matrix[nonzerorow][j];
   // And replace the 'array1' and 'array2' onto 'matrix'.
   for (int j=0; j<col; j++) matrix[index][j] = array2[0][j];
   for (int j=0; j<col; j++) matrix[nonzerorow][j] = array1[0][j];
} 

/* --------------------------------------------------------------- */
/* ----------------------- Basics Methods ------------------------ */
/* --------------------------------------------------------------- */

/* If 'matrix' is square then extract the diagonal matrix from 
it, otherwise raise error. For example:

double matrix[2][2] = {
   {7, 0}, 
   {6, -4},
};
double result[1][2];
diagonal(2, 2, matrix, result);
display_matrix(1, 2, result);

7.000000 -4.000000
*/
void diagonal(int row, int col, double matrix[row][col], 
              double result[1][col]) {
   // Check if 'matrix' is suqare or not. If it is, raise error.
   assert (row == col);
   // Extract the diagonal matrix of 'matrix'.
   for (int i=0; i<row; i++) result[0][i] = matrix[i][i];
}

/* Return true, if 'matrix' is homogen, otherwise return false. 
Homogen matrix means that the last column of 'matrix' contains
just zeros. For example:

double matrix[2][2] = {
   {7, 0}, 
   {-3, 0},
};
int result = ishomogen(2, 2, matrix);
printf("%d\n", result);
1 
*/
bool ishomogen(int row, int col, double matrix[row][col]) {
   // Check the last element of each columns of 'matrix'.
   for (int i=0; i<row; i++) if (matrix[i][col-1] != 0) 
      return false;

   return true;
}

/* Return true, if 'matrix' contains just 0s, otherwise return 
false. For example:
 
double matrix[2][3] = {
   {0, 0, 0}, 
   {0, 0, 0},
};
int result = iszeros(2, 3, matrix);
printf("%d\n", result);
1
*/
bool iszeros(int row, int col, double matrix[row][col]) {
   // Check the all elements of the 'matrix'.
   for (int i=0; i<row; i++)
      for (int j=0; j<col; j++)
         if (matrix[i][j] != 0) return false;

   return true;
}

/* Return true, if 'matrix' contains just 1s, otherwise 
return false. For example:
 
double matrix[2][3] = {
   {1, 1, 1}, 
   {1, 1, 1},
};
int result = isones(2, 3, matrix);
printf("%d\n", result);
1
*/
bool isones(int row, int col, double matrix[row][col]) {
   // Check the all elements of the 'matrix'.
   for (int i=0; i<row; i++)
      for (int j=0; j<col; j++)
         if (matrix[i][j] != 1) return false;

   return true;
}

/* Return true, if 'matrix' is identity, otherwise return 
false. For example:
 
double matrix[3][3] = {
   {1, 0, 0}, 
   {0, 1, 0}, 
   {0, 0, 1},
};
int result = isindetity(3, 3, matrix);
printf("%d\n", result);
1
*/
bool isidentity(int row, int col, double matrix[row][col]) {
   // Check the all elements of the 'matrix'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      if ((i == j && matrix[i][j] != 1) || // check the diagonal,
          (i != j) && matrix[i][j] != 0)  // check the rest.
            return false;
   return true;
}

/* Generate the new zeros matrix. For example:

double result[2][4];
zeros(2, 4, result);
display_matrix(2, 4, result);

0.000000 0.000000 0.000000 0.000000
0.000000 0.000000 0.000000 0.000000
*/
void zeros(int row, int col, double result[row][col]) {
   // Fill the blank spaces with zeros.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = 0.0;
}

/* Generate the new ones matrix. For example:

double result[2][4];
ones(2, 4, result);
display_matrix(2, 4, result);

1.000000 1.000000 1.000000 1.000000
1.000000 1.000000 1.000000 1.000000
*/
void ones(int row, int col, double result[row][col]) {
   // Fill the blank spaces with ones.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = 1.0;
}

/* Generate the new identity matrix. For example:

double result[3][3];
identity(3, 3, result);
display_matrix(1, 3, result);

1.000000 0.000000 0.000000
0.000000 1.000000 0.000000 
0.000000 0.000000 1.000000
*/
void identity(int row, int col, double result[row][col]) {
   // Check if the 'row' and 'col' are same or not.
   assert(row == col);
   // Fill the main diagonal with ones, and the rest with zeros.
   zeros(row, col, result);
   for (int i=0; i<row; i++) result[i][i] = 1.0;
}

/* Generate the new arbitrary matrix. Elements of arbitrary 
matrix are 'value'. For example:

double result[2][3];
arbitrary(4, 2, 3, result);
display_matrix(2, 3, result);

4.000000 4.000000 4.000000
4.000000 4.000000 4.000000 
*/
void arbitrary(double value,  int row, int col, 
               double result[row][col]) {
   // Fill the blank spaces with 'value'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = value;
}

/* Generate the new sequential matrix. Elements of sequential
matrix are between 'initial' and 'end'. For example:

double matrix[3][5];
sequential(1, 15, 3, 5, matrix);
display_matrix(3, 5, matrix);

1.000000 2.000000 3.000000 4.000000 5.000000 
6.000000 7.000000 8.000000 9.000000 10.000000 
11.000000 12.000000 13.000000 14.000000 15.000000
*/
void sequential(int initial, int end, int row, int col, 
                double result[row][col]) {
   // Indicate the step interval.
   double step; 
   // Find the step interval for each two situations.
   if (end - initial > 0) 
      step = (double) (end-initial) / (double) (row*col-1);
   else step = (double) (end-initial) / (double) (row*col-1);

   double total = initial;
   // Fill the 'matrix' with sequential numbers.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      result[i][j] = total, total += step; 
}

/* Generate the new random double matrix. Elements of random
double matrix are between 'initial' and 'end'. For example:

double matrix[2][5];
randouble(-10, 10, 2, 5, matrix);
display_matrix(2, 5, matrix);

6.000000 8.000000 -7.000000 4.000000 -7.000000 
-5.000000 -3.000000 6.000000 -3.000000 -1.000000 
*/
void randouble(int initial, int end, int row, int col, 
               double result[row][col]) {
   // Check the 'end' is bigger or equal to 'initial'.
   assert(end >= initial);
   // Change the seed continualy for generating different integer.
   srand(time(NULL)); double integer;

   // There are 3 cases in here according to sings of parameters.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      // First is that both parameters are positives.
      if (initial >= 0 && end >= 0) {
         while (true) {
            // Generate the random positive integer.
            integer = rand() % (end + 1);
            if (integer >= initial) break;
      }}
      // Second is that 'initial' parameter is negative.
      else if (initial < 0 && end > 0) {
         while (true) {
            // Previously, determine the 'nend' variable.
            int nend;
            if (-initial >= end) nend = -initial;
            else nend = end;
            // Generate the random positive or negative integer.
            integer = rand() % nend;
            // Set the 'integer' to negative if that case is true.
            if (integer > end) {integer *= -1; break;}
            else {
               // The main strategy is to make positive integer if 
               // 'integer' is even and make negative integer if 
               // 'integer' is odd.
               if ((int) integer % 2 == 1 && -integer >= initial) 
                  {integer *= -1; break;}
               if ((int) integer % 2 == 0 && integer >= initial) 
                  break;
      }}}
      // Third is that both parameters are negatives.
      else {
         while (true) {
            // Generate the random negative integer.
            integer = rand() % (-initial + 1);
            if (integer >= -end) {integer *= -1; break;}
      }} 
      // Append the random 'integer' into 'result'.
      result[i][j] = integer;
   }}
}

/* Return true, if the 'matrix1' and 'matrix2' are same, 
otherwise return false. For example:

double matrix1[2][2] = { 
   {7, 4}, 
   {0, 1}, 
};
double matrix2[2][2] = { 
   {7, 4}, 
   {0, 1},
};
int result = isequal(2, 2, matrix1, matrix2);
printf("%d\n", result);
1
*/
bool isequal(int row, int col, double matrix1[row][col], 
             double matrix2[row][col]) {
   // Check the elements of 'matrix1' and 'matrix2'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      if (matrix1[i][j] != matrix2[i][j]) 
         return false; 

   return true;
}

/* Find the highest element in the 'matrix'. For example:

double matrix[3][2] = {
   {1, 7}, 
   {0, -2}, 
   {-4, -2},
}
double result = highest(3, 2, matrix);
prinf("%f\n", result);

7.000000
*/
double highest(int row, int col, double matrix[row][col]) {
   // Assign the first element of 'matrix' as default.
   double high = matrix[0][0];
   // And then find the highest value.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      if (matrix[i][j] > high) high = matrix[i][j]; 

   return high;
}

/* Find the lowest element in the 'matrix'. For example:

double matrix[3][2] = {
   {1, 7}, 
   {0, -2}, 
   {-4, -2},
}
double result = lowest(3, 2, matrix);
prinf("%f\n", result);

-4.000000
*/
double lowest(int row, int col, double matrix[row][col]) {
   // Assign the first element of 'matrix' as default.
   double low = matrix[0][0];
   // And then find the lowest value.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      if (matrix[i][j] < low) low = matrix[i][j]; 

   return low;
}

/* Aggregate the rows of 'matrix' as horizontal. For example: 

double matrix[2][3] = {
   {7, 5, -5}, 
   {7, -1, 3},
};
double result[1][3];
agg_hor(2, 3, matrix, result);
display_matrix(1, 3, result);

14.000000 4.000000 -2.000000
*/
void agg_hor(int row, int col, double matrix[row][col],
             double result[1][col]) {
   // The total value of the rows of 'matrix'.
   double total = 0.0;
   int index = 0;
   // Aggregate the rows of 'matrix'.
}

/* Aggregate the columns of 'matrix' as vertical. For example: 

double matrix[2][3] = {
   {7, 5, -5}, 
   {7, -1, 3},
};
double result[2][1];
agg_ver(2, 3, matrix, result);
display_matrix(2, 1, result);

7.000000 
9.000000
*/
void agg_ver(int row, int col, double matrix[row][col], 
             double result[row][1]) {
   // The total value of the columns of 'matrix'.
   double total = 0.0;
   // Aggregate the columns of 'matrix'.
   for (int i=0; i<row; i++) { for (int j=0; j<col; j++) {
      total += matrix[i][j]; } // sum the columns
      result[i][0] = total; // assign 'total'
      total = 0; } // reset the 'total'
}

/* Generate the transpose of 'matrix'. With another word, 
exchange rows and colulmns of 'matrix'. For example: 

double matrix[3][2] = {
   {7, 5}, 
   {-1, 3}, 
   {0, -5},
};
double result[2][3];
transpose(3, 2, matrix, result);
display_matrix(2, 3, result);

7.000000 -1.000000 0.000000 
5.000000 3.000000 -5.000000
*/
void transpose(int row, int col, double matrix[row][col], 
               double result[col][row]) {
   // Exchange the rows and columns of 'matrix'.
   for (int i=0; i<row; i++) 
      for (int j=0; j<col; j++)
         result[j][i] = matrix[i][j];
}

/* Return true, if the 'matrix' is lower triangular, otherwise
return false. For example: 

double matrix[4][4] = {
   {1, 0, 0, 0}, 
   {2, 4, 0, 0}, 
   {6, 7, 8, 0}, 
   {5, 7, 4, 5}, 
};
int result = islowertri(4, 4, matrix);
printf("%d\n", result);
1
*/
bool islowertri(int row, int col, double matrix[row][col]) {
   // Lower triangular matrix must be squre.
   if (row != col) return false;
   // Collect the upper side of 'matrix'.
   double ltri[(row * col - row) / 2]; int index = 0;
   for (int i=0; i<row-1; i++) for (int j=i+1; j<col; j++) 
      ltri[index] = matrix[i][j], index ++; 
   // Control the elements of 'ltri'. If any element is not 
   // zero, and then return false.
   for (int i=0; i<index; i++)
      if (ltri[i] != 0.0) return false;

   return true;
}

/* Return true, if the 'matrix' is upper triangular, otherwise
return false. For example: 

double matrix[4][4] = {
   {1, 2, 6, 5},  
   {0, 4, 7, 7},  
   {0, 0, 8, 4}, 
   {0, 0, 0, 5},
};
int result = isuppertri(4, 4, matrix);
printf("%d\n", result);
1
*/
bool isuppertri(int row, int col, double matrix[row][col]) {
   // That method can be generated from above method. 
   // Firsly, get the transpose of 'matrix'.
   double utri[col][row]; transpose(row, col, matrix, utri);
   // And then check it using 'islowertri' method.
   if (islowertri(col, row, utri)) return true;
   else return false;
}

/* Return true, if the 'matrix' is upper or lower triangular, 
otherwise return false. For example: 

double matrix[3][3] = {
   {1, 2, 6},  
   {0, 4, 7},  
   {0, 0, 8}, 
};
int result = istriangle(3, 3, matrix);
printf("%d\n", result);
1
*/
bool istriangle(int row, int col, double matrix[row][col]) {
   // Use the above two methods for that.
   int isltri = islowertri(row, col, matrix);
   int isutri = isuppertri(row, col, matrix);
   if (isltri || isutri) return true;
   else return false;
}

/* Calculate the mean of 'matrix'. For exapmle: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -8}, 
   {-5, 1, 4}, 
};
double result = mean(3, 3, matrix);
printf("%f\n", result);

0.555556
*/
double mean(int row, int col, double matrix[row][col]) {
   // The total value of 'matrix'.
   double total;
   // Sum the all elements of 'matrix'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      total += matrix[i][j];

   return total / (row * col);
}

/* Sort the elements of 'matrix' in ascending order. 
For example: 

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result[3][4];
sort_asc(3, 4, matrix, result);
display_matrix(3, 4, result);

-8.000000 -8.000000 -5.000000 -4.000000 
0.000000 0.000000 1.000000 2.000000 
4.000000 7.000000 7.000000 8.000000
*/
void sort_asc(int row, int col, double matrix[row][col], 
              double result[row][col]) {
   // Convert the 'matrix' to the 'array'.
   double array[row * col]; 
   _to_array_(row, col, matrix, array);
   int temp = 0;
   // Sort the elements of 'array'.
   for (int i=0; i<row*col; i++)
      for (int j=0; j<row*col; j++)
         if (array[i] < array[j]) temp = array[i], 
            array[i] = array[j], array[j] = temp;
   // Lastly, convert the sorted 'array' to 'result'.
   _to_matrix_(row, col, array, result);
}

/* Sort the elements of 'matrix' in descending order. For example: 

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result[3][4];
sort_des(3, 4, matrix, result);
display_matrix(3, 4, result);

8.000000 7.000000 7.000000 4.000000 
2.000000 1.000000 0.000000 0.000000 
-4.000000 -5.000000 -8.000000 -8.000000
*/
void sort_des(int row, int col, double matrix[row][col], 
              double result[row][col]) {
   // Convert the 'matrix' to the 'array'.
   double array[row * col]; 
   _to_array_(row, col, matrix, array);
   int temp = 0;
   // Sort the elements of 'array'.
   for (int i=0; i<row*col; i++)
      for (int j=0; j<row*col; j++)
         if (array[i] > array[j]) temp = array[i], 
            array[i] = array[j], array[j] = temp;
   // Lastly, convert the sorted 'array' to 'result'.
   _to_matrix_(row, col, array, result);
}

/* Calculate the standard deviation of 'matrix'. For example:

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result = stddev(3, 4, matrix);
printf("%f\n", result);

5.405758
*/
double stddev(int row, int col, double matrix[row][col]) {
   // Calculate the mean of 'matrix'.
   double m = mean(row, col, matrix);
   double pows = 0; // sum the pows
   // Iterate and process the each element of 'matrix'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) {
      // Get the differences between 'mean' and elements.
      double diff = m - matrix[i][j];
      // According to sign of 'diff', sum the pow of it.
      if (diff < 0) pows += pow(-1 * diff,  2);
      else pows += pow(diff, 2);
   }
   // Get the squre root of result, and then return it.
   return sqrt(pows / (row * col));
}

/* Find the median element of 'matrix'. For example: 

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result = median(3, 4, matrix);
printf("%f\n", result);

0.500000
*/
double median(int row, int col, double matrix[row][col]) {
   // Sort the all elements of 'matrix' is ascendng form.
   double sorted[row][col]; 
   sort_des(row, col, matrix, sorted);
   // Convert the 'sorted' matrix to 'array'.
   double array[row * col];
   _to_array_(row, col, sorted, array);
   // And then determine the median.
   if ((row * col) % 2 == 1)
      return array[(int) (row * col / 2)];
   else {
      int first = (int) (row * col / 2) - 1;
      int second = (int) (row * col / 2);
      return (array[first] + array[second]) / 2;
   }
}

/* Shuffle the elements of 'matrix' randomly. For example: 

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result[3][4];
shuffle(3, 4, matrix, result);
display_matrix(3, 4, result);

4.000000 8.000000 7.000000 -4.000000 
7.000000 0.000000 0.000000 -8.000000 
2.000000 -5.000000 -8.000000 1.000000
*/
void shuffle(int row, int col, double matrix[row][col], 
             double result[row][col]) {
   // Convert the 'matrix' into 'array'.
   double array[row * col]; _to_array_(row, col, matrix, array);
   // Generate the random indexes between 0 and row*col-1.
   int indexes[row * col]; 
   // Adjust the seed for generating indexes contigously.
   srand(time(NULL)); int start = 0;
   while (true) {
      // Generate the random index.
      int index = rand() % (row * col);
      // Each index can be found for one time in 'indexes'.
      int existance = 0;
      // To check this, in each time, count the existance of it.
      for (int i=0; i<start; i++) if (indexes[i] != index) 
         existance ++;
      if (existance == start) indexes[start] = index, start ++;
      // Break up the loop if 'start' reach its max value. 
      if (start == row*col) break;
   }
   start = 0; 
   // Put the elements of 'matrix' into 'result'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = array[indexes[start]], start ++;
}


/* Reshape dimension of 'matrix' and then convert it to 'result'.
For example: 

double matrix[3][4] = {
   {2, -4, 0, -8}, 
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result[2][6];
reshape(3, 4, matrix, 2, 6, result);
display_matrix(2, 6, result);

2.000000 -4.000000 0.000000 -8.000000 8.000000 7.000000 
-8.000000 7.000000 -5.000000 1.000000 4.000000 0.000000
*/
void reshape(int row1, int col1, double matrix[row1][col1], 
             int row2, int col2, double result[row2][col2]) {
   // Check if the dimensions of 'matrix' and 'result' are same.
   assert (row1 * col1 == row2 * col2);
   // Convert 'matrix' into 'array'.
   double array[row1 * col1]; int index = 0;
   _to_array_(row1, col1, matrix, array);
   // Assign the elements of 'array' into 'result'.
   for (int i=0; i<row2; i++) for (int j=0; j<col2; j++)
      result[i][j] = array[index], index ++;
}

/* Concatenate the 'matrix1' and 'matrix2' as horizontal. 
For example: 

double matrix1[1][4] = {
   {2, -4, 0, -8}, 
};
double matrix2[2][4] = {
   {8, 7, -8, 7}, 
   {-5, 1, 4, 0}, 
};
double result[3][4];
concat_hor(1, 4, matrix1, 2, 4, matrix2, result);
display_matrix(3, 4, result);

2.000000 -4.000000 0.000000 -8.000000 
8.000000 7.000000 -8.000000 7.000000 
-5.000000 1.000000 4.000000 0.000000 
*/
void concat_hor(int row1, int col1, double matrix1[row1][col1], 
                int row2, int col2, double matrix2[row2][col2], 
                double result[row1 + row2][col1]) {
   // Check the dimension harmony of 'matrix1' and 'matrix2'.
   assert (col1 == col2);
   // Concatenate the both matrix onto 'result'.
   for (int i=0; i<row1; i++) for (int j=0; j<col1; j++)
      result[i][j] = matrix1[i][j];
   for (int i=0; i<row2; i++) for (int j=0; j<col2; j++)
      result[i+row1][j] = matrix2[i][j];
}

/* Concatenate the 'matrix1' and 'matrix2' as vertical. 
For example: 

double matrix1[3][3] = {
   {2, -4, 0}, 
   {8, 7, -8}, 
   {-5, 1, 4},
};
double matrix2[3][1] = {
   {-8}, 
   {7}, 
   {0},
};
double result[3][4];
concat_ver(3, 3, matrix1, 3, 1, matrix2, result);
display_matrix(3, 4, result);

2.000000 -4.000000 0.000000 -8.000000 
8.000000 7.000000 -8.000000 7.000000 
-5.000000 1.000000 4.000000 0.000000 
*/
void concat_ver(int row1, int col1, double matrix1[row1][col1], 
                int row2, int col2, double matrix2[row2][col2], 
                double result[row1][col1 + col2]) {
   // Check the dimension harmony of 'matrix1' and 'matrix2'.
   assert (row1 == row2);
   // Concatenate the both matrix onto 'result'.
   for (int i=0; i<row1; i++) for (int j=0; j<col1; j++)
      result[i][j] = matrix1[i][j];
   for (int i=0; i<row2; i++) for (int j=0; j<col2; j++)
      result[i][j+col1] = matrix2[i][j];
}

/* Add the elements of 'matrix1' and 'matrix2'. For example: 

double matrix1[2][2] = {
   {2, -4}, 
   {8, 7}, 
};
double matrix2[2][2] = {
   {-2, 4}, 
   {-8, -7}, 
};
double result[2][2];
add(2, 2, matrix1, matrix2, result);
display_matrix(2, 2, result);

0.000000 0.000000 
0.000000 0.000000
*/
void add(int row, int col, double matrix1[row][col], 
         double matrix2[row][col], double result[row][col]) {
   // Add the elements with each other mutually.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      result[i][j] = matrix1[i][j] + matrix2[i][j]; 
}

/* Subtract the elements of 'matrix2' from 'matrix1'. 
For example:

double matrix1[2][2] = {
   {2, -4}, 
   {8, 7}, 
};
double matrix2[2][2] = {
   {-2, 4}, 
   {-8, -7}, 
};
double result[2][2];
add(2, 2, matrix1, matrix2, result);
display_matrix(2, 2, result);

4.000000 -8.000000 
16.000000 14.000000
*/
void subtract(int row, int col, double matrix1[row][col], 
              double matrix2[row][col], double result[row][col]) {
   // Subtract the elements with each other mutually.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      result[i][j] = matrix1[i][j] - matrix2[i][j]; 
}

/* Multiplies 'scaler' and elements of 'matrix'. For example: 

double matrix[2][2] = {
   {2, -4}, 
   {8, 7}, 
};
double result[2][2];
scaler_mul(-4.8, 2, 2, matrix, result);
display_matrix(2, 2, result);

-9.600000 19.200000 
-38.400000 -33.600000
*/
void scaler_mul(double scaler, int row, int col, 
                double matrix[row][col], double result[row][col]) {
   // Multiply the elements of 'matrix' with 'scaler'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      result[i][j] = matrix[i][j] * scaler; 
}


/* Multiplies the elements of 'matrix1' and 'matrix2' as dot. 
For example:

double matrix1[2][2] = {
   {2, -4}, 
   {8, 7}, 
};
double matrix2[2][2] = {
   {-2, 4}, 
   {-8, -7}, 
};
double result[2][2];
dot_mul(2, 2, matrix1, matrix2, result);
display_matrix(2, 2, result);

-4.000000 -16.000000 
-64.000000 -49.000000
*/
void dot_mul(int row, int col, double matrix1[row][col], 
             double matrix2[row][col], double result[row][col]) {
   // Multiply the elements with each other mutually.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      result[i][j] = matrix1[i][j] * matrix2[i][j];
}

/* Multiply the elements of 'matrix1' and 'matrix2' as cross.
For example: 

double matrix1[2][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
};
double matrix2[3][2] = {
   {-2, 4}, 
   {-8, -7}, 
   {9, 7}, 
};
double result[2][2];
cross_mul(2, 3, matrix1, 3, 2, matrix2, result);
display_matrix(2, 2, result);

28.000000 36.000000 
-117.000000 -52.000000
*/
void cross_mul(int row1, int col1, double matrix1[row1][col1], 
               int row2, int col2, double matrix2[row2][col2], 
               double result[row1][col2]) {
   // Check the dimension harmony of the matrices.
   assert (col1 == row2);
   // Get the transpose of 'matrix2'.
   double transposed[col2][row2];
   transpose(row2, col2, matrix2, transposed);
   // These variable is necassery when multiply the elements.
   double total = 0; int index = col1; int start = 0;
   double array[row1 * col2];
   // Iterate the elements of 'matrix1' and 'matrix2'.
   for (int i=0; i<row1; i++)
      for (int j=0; j<col2; j++)
         for (int k=0; k<row2; k++) {
            // Multiply the elements with each other.
            double value = matrix1[i][k] * transposed[j][k];
            total += value; index --;
            // Save the results onto 'array'.
            if (index == 0) array[start] = total, 
            total = 0, index = col1, start ++;
         }
   // Fill the 'result' with elements of 'array'.
   _to_matrix_(row1, col2, array, result);
}

/* Divide the 'scaler' to elements of 'matrix'. For example: 

double matrix[2][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
};
double result[2][3];
scaler_div(0.5, 2, 3, matrix, result);
display_matrix(2, 3, result);

4.000000 -8.000000 0.000000 
16.000000 14.000000 -10.000000 
*/
void scaler_div(double scaler, int row, int col, 
                double matrix[row][col], double result[row][col]){
   // Iterate the elements of 'matrix' and divide it.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = matrix[i][j] / scaler;
}

/* Divide the elements of 'matrix1' to 'matrix2'. For example: 

double matrix1[2][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
};
double matrix2[2][3] = {
   {3, 8, -3}, 
   {5, -5, 0},  
};
double result[2][3];
dot_div(2, 3, matrix1, matrix2, result);
display_matrix(2, 3, result); 

0.666667 -0.500000 -0.000000 
1.600000 -1.400000 -inf
*/
void dot_div(int row, int col, double matrix1[row][col], 
             double matrix2[row][col], double result[row][col]){
   // Iterate the elements of 'matrix' and divide it.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++)
      result[i][j] = matrix1[i][j] / matrix2[i][j];
}

/* --------------------------------------------------------------- */
/* --------------------- Advanced Methods ------------------------ */
/* --------------------------------------------------------------- */

/* Extract the upper triangle from 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
uppertri(3, 3, matrix, result);
display_matrix(3, 3, result);

2.000000 -4.000000 0.000000 
0.000000 23.000000 -5.000000 
0.000000 0.000000 12.000000
*/
void uppertri(int row, int col, double matrix[row][col], 
              double result[row][col]) {
   // Check if 'matrix' is square or not.
   assert (row == col);
   // Copy the 'matrix' to 'result' initially.
   _copy_matrix_(row, col, matrix, result);
   // Control the iteration number with 'k' variable.
   int k = 0;
   // Step by step, generate the upper triangular matrix.
   while (true) {
      // Iterate the all elements of 'matrix'.
      for (int i=1+k; i<row; i++) {
         // Generally, these sub-matrices will be generated.
         double m1[1][col]; double m2[1][col]; 
         double m3[1][col]; double m4[1][col];
         // If there is a zero, if main diagonal contains zero.
         if (result[k][k] == 0.0) 
               _switch_rows_(row, col, result, k);
         // Calculate the coefficients in each time.  
         double coef = -1 * result[i][k] / result[k][k];
         // Generate the sub-matrices and fill in it.
         for (int j=0; j<col; j++) m1[0][j] = result[k][j];
         for (int j=0; j<col; j++) m2[0][j] = result[i][j];
         // Multiply the 'm2' matrix with 'coef'.
         scaler_mul(coef, 1, col, m1, m3);
         // Add up the 'm2' matrix and 'm3' matrix.
         add(1, col, m2, m3, m4);
         // Replace the old row with new 'm4' row.
         for (int j=0; j<col; j++) result[i][j] = m4[0][j];
      }
      // Update the control variable in each iteration.
      k ++;
      // Break up the loop if necassary condition are provided.
      if (k == row) break;
   }
}

/* Calculate the determinant of square 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result = det(3, 3, matrix);
printf("%f\n", result);

552.000000
*/
double det(int row, int col, double matrix[row][col]) {
   // Check if 'matrix' is square or not.
   assert (row == col);
   // Calculate the determinant of 1x1 matrix.
   if (row == 1) return matrix[0][0];
   // Calculate the determinant of 2x2 matrix.
   if (row == 2) {
      // Multiply the diagonals and get the difference.
      double s1 = matrix[0][0] * matrix[1][1];
      double s2 = matrix[0][1] * matrix[1][0];
      return s1 - s2;
   }
   // Calculate the determinant of 3x3 and more matrix.
   if (row >= 3) {
      // Can be used 'uppertri' method for this.
      double uppertri[row][col];
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
            double m1[1][col]; double m2[1][col]; 
            double m3[1][col]; double m4[1][col];
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
            double coef = -1 * uppertri[i][k] / uppertri[k][k];
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
      double det = 1.0;
      // multiply the main diagonal elements of 'uppertri' matrix.
      for (int i=0; i<row; i++) det *= uppertri[i][i];

      return det * pow(-1, switching);
   }
}

/* Extract the minors map of 'matrix'. For example:

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
minors(3, 3, matrix3, result);
display_matrix(3, 3, result);

84.000000 96.000000 0.000000 
-28.000000 14.000000 46.000000 
20.000000 -10.000000 46.000000
*/
void minors(int row, int col, double matrix[row][col], 
            double result[row][col]) {
   // Check if the 'matrix' is proper form for that.
   assert (row == col || row != 1 || col != 1);
   // Iterate the elements of 'matrix'.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) {
      // Copy the 'matrix' in here. 
      double copied[row][col]; 
      _copy_matrix_(row, col, matrix, copied); 
      // Parse just the 'matrix' according to first row.
      double parsed[row-1][col]; 
      _del_row_(i, row, col, copied, parsed);
      // Get the transpose of 'deleted'.
      double transposed[col][row-1]; 
      transpose(row-1, col, parsed, transposed);
      // Delete the again first row of 'transposed'.
      double parsed2[col-1][row-1];
      _del_row_(j, col, row-1, transposed, parsed2);
      // Again transposed the 'deleted2' matrix.
      double transposed2[row-1][col-1];
      transpose(col-1, row-1, parsed2, transposed2);
      // Calculate the determinant of reduced 'matrix' and 
      // then replace it into 'result' matrix.
      result[i][j] = det(row-1, col-1, transposed2); 
   }
}

/* Extract the cofactors map of 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
cofactors(3, 3, matrix, result);
display_matrix(3, 3, result);

84.000000 -96.000000 0.000000 
28.000000 14.000000 -46.000000 
20.000000 10.000000 46.000000 
*/
void cofactors(int row, int col, double matrix[row][col], 
               double result[row][col]) {
   // Check if given 'matrix' is proper for this method.
   assert (row == col || row != 1 || col != 1);
   // Extract the minors map of 'matrix'.
   minors(row, col, matrix, result);
   // Multiply the elements that is odd of sum of indexes by -1.
   for (int i=0; i<row; i++) for (int j=0; j<col; j++) 
      if ((i+j) % 2 == 1 && result[i][j] != 0.0)            
         result[i][j] = -1 * result[i][j];     
}

/* Return true, if 'matrix' is invertible (its determinant is 
different from zero), otherwise return false. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
int result = isinvertible(3, 3, matrix);
printf("%d\n", result);
1
*/
bool isinvertible(int row, int col, double matrix[row][col]) {
   // Calculate the determinant of 'matrix'.
   double determinant = det(row, col, matrix);
   if (determinant != 0.0) return true;
   else return false;
}

/* Calculate the adjoint of 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
adjoint(3, 3, matrix, result);
display_matrix(3, 3, result);

84.000000 28.000000 20.000000 
-96.000000 14.000000 10.000000 
0.000000 -46.000000 46.000000
*/
void adjoint(int row, int col, double matrix[row][col], 
            double result[row][col]) {
   // Extract the cofactors map into 'cofactor'.
   double cofactor[row][col]; 
   cofactors(row, col, matrix, cofactor);
   // Get transpose of 'cofactor' into 'result'.
   transpose(row, col, cofactor, result);
}

/* Calculate the inverse of 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
inverse(3, 3, matrix, result);
display_matrix(3, 3, result);

0.152174 0.050725 0.036232 
-0.173913 0.025362 0.018116 
0.000000 -0.083333 0.083333
*/
void inverse(int row, int col, double matrix[row][col], 
             double result[row][col]) {
   // Check if 'matrix' is invertible or not.
   assert (isinvertible(row, col, matrix));
   // Calculate the determinant of 'matrix'.
   double determinant = det(row, col, matrix);
   // Extract the adjoint of 'matrix'.
   double adj[row][col]; adjoint(row, col, matrix, adj);
   // Calculate the inverse with 'scaler_div' method.
   scaler_div(determinant, row, col, adj, result);
}

/* Extract the lower triangle from 'matrix'. For example: 

double matrix[3][3] = {
   {2, -4, 0}, 
   {8, 7, -5}, 
   {8, 7, 7}, 
};
double result[3][3];
lowertri(3, 3, matrix, result);
display_matrix(3, 3, result);

1.000000 0.000000 0.000000 
4.000000 1.000000 0.000000 
4.000000 1.000000 1.000000
*/
void lowertri(int row, int col, double matrix[row][col], 
              double result[row][col]) {
   // Check if the 'matrix' is squre or not.
   assert (row == col);
   // Previously, extract the upper triangle from 'matrix'. 
   double utri[row][col];
   uppertri(row, col, matrix, utri);
   // Get the inverse of upper triangle from 'matrix'.
   double inv[row][col];
   inverse(row, col, utri, inv);
   // Multiply the inverse of triangle matrix and 'matrix'.
   cross_mul(row, col, matrix, row, col, inv, result);
}

/* Solve a linear augmented matrix. For example: 

double matrix[3][4] = {
   {2, -4, 0, 8}, 
   {8, 7, -5, -9}, 
   {8, 7, 7, 0}, 
};
double result[3][1];
solve(3, 4, matrix, result);
display_matrix(3, 1, result);

0.760870 
-1.619565 
0.750000
*/
void solve(int row, int col, double matrix[row][col], 
           double result[row][1]) {
   // Check if 'matrix' is proper form for solving equations.
   assert (col - row == 1);
   // Extract the main square and target matrices.
   double smatrix[row][col-1]; 
   double target[row][1];
   // Iterate the 'matrix' elements.
   for (int i=0; i<row; i++) for (int j=0; j<col-1; j++) 
      smatrix[i][j] = matrix[i][j]; 
   for (int i=0; i<row; i++) target[i][0] = matrix[i][col-1];
   // Check if the 'smatrix' is invertible or not.
   assert (isinvertible(row, col-1, smatrix));
   // Get inverse or 'smatrix'.
   double inv[row][col-1]; 
   inverse(row, col-1, smatrix, inv);
   // Multiply the 'inv' and 'target' matrices as cross.
   cross_mul(row, col-1, inv, row, 1, target, result);
}
