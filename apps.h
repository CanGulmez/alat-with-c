/* Some applications in ALAT (Advanced Linear Algebra Toolkit) 

In this source file, I've focused 4 basics applications related 
with linear algera. These are polynomial curve fitting, least 
square regression, area of triangle using determinant and volume 
of tetrahedron using determinant. I hope, it will be useful...

+ poly_curve_fitting
+ least_squares_reg
+ area
+ volume

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "matrices.h"

/* Polynomial Curve Fitting */
void poly_curve_fitting(int len, float x_points[len], 
                        float y_points[len], float result[len]) {

   // Process 'xs' points and generate the 'xsmatrix'.
   float xsmatrix[len][len]; 
   // Iterate the 'xs' pointsç
   for (int i=0; i<len; i++) { 
      int index = 0; int bound = len; 
      while (true) {
         float value = pow(x_points[i], index);
         xsmatrix[i][index] = value; index++;
         // Break up the loop.
         if (index == bound) break; }
   }
   // Get the inverse of 'xsmatrix' matrix.
   if (isinvertible(len, len, xsmatrix) == false) {
      puts("AppsError: 'xsmatrix' must be invertible");
      exit(EXIT_FAILURE);
   }
   xsmatrix[len][len]; inverse(len, len, xsmatrix, xsmatrix);
   // Convert the 'ys' array to the matrix.
   float ysmatrix[1][len]; 
   for (int i=0; i<len; i++) ysmatrix[0][i] = y_points[i];
   // Get the transpose of 'ysmatrix'.
   ysmatrix[len][1]; transpose(1, len, ysmatrix, ysmatrix);
   // Multiply the 'xsmatrix' and 'ysmatrix' with each other.
   float mul[len][1]; 
   cross_mul(len, len, xsmatrix, len, 1, ysmatrix, mul);
   // Transmit the results onto 'result' array.
   for (int i=0; i<len; i++) result[i] = mul[i][0];
}

/* Least Squares Regression */
void least_squares_reg(int len, float x_points[len], 
                       float y_points[len], float result[2]) {
   // Initially, generate the ones matrix and then
   float matrix[2][len]; ones(2, len, matrix);
   // replace the elements with 'xs'.
   for (int i=0; i<len; i++) matrix[1][i] = x_points[i];
   // Get the transpose of 'matrix'.
   float tmatrix[len][2]; transpose(2, len, matrix, tmatrix);
   // Create the target matrix and then
   float target[1][len]; 
   for (int i=0; i<len; i++) target[0][i] = y_points[i];
   // get the tranpose of 'target' as well.
   float ttarget[len][1]; transpose(1, len, target, ttarget);
   // Multiply the 'matrix' and 'tmatrix' as cross.
   float cmul1[2][2]; 
   cross_mul(2, len, matrix, len, 2, tmatrix, cmul1);
   // Multiply the 'matrix' and 'target' as cross.
   float cmul2[2][1]; 
   cross_mul(2, len, matrix, len, 1, ttarget, cmul2);
   // Get the cofactors of 'cmul1'.
   float cofact[2][2]; cofactors(2, 2, cmul1, cofact);
   // Multiply the 'cofact' and 'cmul2' as cross.
   float cmul3[2][1]; 
   cross_mul(2, 2, cofact, 2, 1, cmul2, cmul3);
   // Multiply the 'cmul3' with a scaler.
   float smul[2][1]; scaler_mul(0.02, 2, 1, cmul3, smul);
   // Append the results onto 'result' array.
   result[0] = smul[0][0]; result[1] = smul[1][0];
}

/* Calculate the area of triangle using determinant */
float area(float coor1[2], float coor2[2], float coor3[2]) {
   // Generate the ones 'matrix' and then replace the
   float matrix[3][3]; ones(3, 3, matrix);
   // elements with coordinates.
   matrix[0][0] = coor1[0]; matrix[0][1] = coor2[0];
   matrix[0][2] = coor3[0]; matrix[1][0] = coor1[1];
   matrix[1][1] = coor2[1]; matrix[1][2] = coor3[1];
   // Get the transpose of 'matrix'.
   float tmatrix[3][3]; transpose(3, 3, matrix, tmatrix);
   // Calculate the area using determinant.
   float area = det(3, 3, tmatrix) / 2;
   if (area < 0) area = -1 * area;

   return area;
}

/* Calculate the volume of tetrahedron using determinant */
float volume(float coor1[3], float coor2[3], float coor3[3], 
             float coor4[3]) {
   // Collect the points in 'matrix'. Initially, generate the ones
   // matrix and then replace the elements with points.
   float matrix[4][4]; ones(4, 4, matrix);
   matrix[0][0] = coor1[0]; matrix[0][1] = coor2[0]; 
   matrix[0][2] = coor3[0]; matrix[0][3] = coor4[0];
   matrix[1][0] = coor1[1]; matrix[1][1] = coor2[1]; 
   matrix[1][2] = coor3[1]; matrix[1][3] = coor4[1];
   matrix[2][0] = coor1[2]; matrix[2][1] = coor2[2]; 
   matrix[2][2] = coor3[2]; matrix[2][3] = coor4[2];
   // Get the tranpose of 'matrix'.
   float tmatrix[4][4]; transpose(4, 4, matrix, tmatrix);
   // Calculate the volume using determinant.
   float volume = det(4, 4, tmatrix) / 6;
   if (volume < 0) volume = -1.0 * volume;

   return volume;
}
