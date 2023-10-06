/* Some applications in ALAT (Advanced Linear Algebra Toolkit) 

Methods: 
   poly_curve_fitting(), least_squares_reg(), area(), volume()
*/

/* Libraries */
#include <stdbool.h>
#include <math.h>
#include "matrices.h"

/* --------------------------------------------------------------- */
/* ------------------------ Basics Methods ----------------------- */
/* --------------------------------------------------------------- */

/* Polynomial curve fitting. For example: 

double xpoints[3] = {1, 2, 3}; // x axis points
double ypoints[3] = {4, 0, 12}; // y asix points
double result[3];
poly_curve_fitting(3, xpoints, ypoints, result);
display_array(3, result);

24.000000 -28.000000 8.000000 // f(x) = 24.0 - 28.0x + 8.0x**2
*/
void poly_curve_fitting(int len, double xpoints[len], 
                        double ypoints[len], double result[len]){
   // Process 'xs' points and generate the 'xsmatrix'.
   double xsmatrix[len][len]; 
   // Iterate the 'xs' pointsç
   for (int i=0; i<len; i++) { 
      int index = 0; int bound = len; 
      while (true) {
         double value = pow(xpoints[i], index);
         xsmatrix[i][index] = value, index++;
         // Break up the loop.
         if (index == bound) break; }
   }
   // Check if the 'xsmatrix' is invertible.
   assert (isinvertible(len, len, xsmatrix));
   // Get the inverse of 'xsmatrix' matrix.
   xsmatrix[len][len]; inverse(len, len, xsmatrix, xsmatrix);
   // Convert the 'ys' array to the matrix.
   double ysmatrix[1][len]; 
   for (int i=0; i<len; i++) ysmatrix[0][i] = ypoints[i];
   // Get the transpose of 'ysmatrix'.
   ysmatrix[len][1]; transpose(1, len, ysmatrix, ysmatrix);
   // Multiply the 'xsmatrix' and 'ysmatrix' with each other.
   double mul[len][1]; 
   cross_mul(len, len, xsmatrix, len, 1, ysmatrix, mul);
   // Transmit the results onto 'result' array.
   for (int i=0; i<len; i++) result[i] = mul[i][0];
}

/* Least squares regression. For example: 

double xpoints[5] = {1, 2, 3, 4, 5}; // x axis points
double ypoints[5] = {1, 2, 4, 4, 6}; // y asix points
double result[2];
least_squares_reg(5, xpoints, ypoints, result);
display_array(2, result);

-0.200000 1.200000 // f(x) = -0.2 + 1.2x
*/
void least_squares_reg(int len, double xpoints[len], 
                       double ypoints[len], double result[2]) {
   // Initially, generate the ones matrix and then
   double matrix[2][len]; ones(2, len, matrix);
   // replace the elements with 'xs'.
   for (int i=0; i<len; i++) matrix[1][i] = xpoints[i];
   // Get the transpose of 'matrix'.
   double tmatrix[len][2]; transpose(2, len, matrix, tmatrix);
   // Create the target matrix and then
   double target[1][len]; 
   for (int i=0; i<len; i++) target[0][i] = ypoints[i];
   // get the tranpose of 'target' as well.
   double ttarget[len][1]; transpose(1, len, target, ttarget);
   // Multiply the 'matrix' and 'tmatrix' as cross.
   double cmul1[2][2]; 
   cross_mul(2, len, matrix, len, 2, tmatrix, cmul1);
   // Multiply the 'matrix' and 'target' as cross.
   double cmul2[2][1]; 
   cross_mul(2, len, matrix, len, 1, ttarget, cmul2);
   // Get the cofactors of 'cmul1'.
   double cofact[2][2]; cofactors(2, 2, cmul1, cofact);
   // Multiply the 'cofact' and 'cmul2' as cross.
   double cmul3[2][1]; 
   cross_mul(2, 2, cofact, 2, 1, cmul2, cmul3);
   // Multiply the 'cmul3' with a scaler.
   double smul[2][1]; scaler_mul(0.02, 2, 1, cmul3, smul);
   // Append the results onto 'result' array.
   result[0] = smul[0][0]; result[1] = smul[1][0];
}

/* Calculate the area of triangle using determinant. For 
example:

double coor1[2] = {1, 0};
double coor2[2] = {2, 2};
double coor3[2] = {4, 3};
double result = area(coor1, coor2, coor3);
printf("%f\n", result);

1.500000
*/
double area(double coor1[2], double coor2[2], double coor3[2]) {
   // Generate the ones 'matrix' and then replace the
   double matrix[3][3]; ones(3, 3, matrix);
   // elements with coordinates.
   matrix[0][0] = coor1[0]; matrix[0][1] = coor2[0];
   matrix[0][2] = coor3[0]; matrix[1][0] = coor1[1];
   matrix[1][1] = coor2[1]; matrix[1][2] = coor3[1];
   // Get the transpose of 'matrix'.
   double tmatrix[3][3]; transpose(3, 3, matrix, tmatrix);
   // Calculate the area using determinant.
   double area = det(3, 3, tmatrix) / 2;

   return (area < 0) ? (-1.0 * area) : area;
}

/* Calculate the volume of tetrahedron using determinant. For 
example: 

double coor1[3] = {0, 4, 1};
double coor2[3] = {4, 0, 0};
double coor3[3] = {3, 5, 2};
double coor4[3] = {2, 2, 5};
double result = volume(coor1, coor2, coor3, coor4);
printf("%f\n", result);

12.000000
*/
double volume(double coor1[3], double coor2[3], double coor3[3], 
              double coor4[3]) {
   // Collect the points in 'matrix'. Initially, generate the ones
   // matrix and then replace the elements with points.
   double matrix[4][4]; ones(4, 4, matrix);
   matrix[0][0] = coor1[0]; matrix[0][1] = coor2[0]; 
   matrix[0][2] = coor3[0]; matrix[0][3] = coor4[0];
   matrix[1][0] = coor1[1]; matrix[1][1] = coor2[1]; 
   matrix[1][2] = coor3[1]; matrix[1][3] = coor4[1];
   matrix[2][0] = coor1[2]; matrix[2][1] = coor2[2]; 
   matrix[2][2] = coor3[2]; matrix[2][3] = coor4[2];
   // Get the tranpose of 'matrix'.
   double tmatrix[4][4]; transpose(4, 4, matrix, tmatrix);
   // Calculate the volume using determinant.
   double volume = det(4, 4, tmatrix) / 6;

   return (volume < 0) ? (-1.0 * volume) : volume;
}
