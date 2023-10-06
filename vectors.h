/* Vector operations in ALAT (Advanced Linear Algebra Toolkit) 

Methods: 
   lenght(), isequal(), iszero(), unit(), add(), scaler_mul(), 
   distance(), dot_mul(), iscs(), istriangle(), ispythag(), 
   angle(), issteep(), isparallel()
*/

/* Libraries */
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>

/* --------------------------------------------------------------- */
/* ------------------------ Basics Methods ----------------------- */
/* --------------------------------------------------------------- */

/* Calculate the lenght of 'vector'. For example:

double vector[2] = {3, 4};
double result = lenght(2, vector);
printf("%f\n", result); 
 
5.000000
*/
double lenght(int dim, double vector[dim]) {
   // Get the all powers of elements of 'vector',
   double pow = 0;
   for (int i=0; i<dim; i++) 
      // and then sum those powers.
      pow += vector[i] * vector[i];
   
   return sqrt(pow);
}

/* Return true, if 'vector1' and 'vector2' are eqauls. 
For example:

double vector1[3] = {0, 4, -3};
double vector2[3] = {0, 4, -3};
int result = isequal(3, vector1, vector2);
printf("%d\n", result);
1 
*/
bool isequal(int dim, double vector1[dim], double vector2[dim]) {
   // Iterate and check the elements.
   for (int i=0; i<dim; i++)
      if (vector1[i] != vector2[i])
         return false;

   return true;
}

/* Return true, if the all elements of 'vector' are zero. 
For example:

double vector[3] = {0, 0, 0};
int result = iszeros(3, vector);
printf("%d\n", result); 
1
*/
bool iszeros(int dim, double vector[dim]) {
   // Iterate and check the elements.
   for (int i=0; i<dim; i++)
      if (vector[i] != 0)
         return false;

   return true;
}

/* Generate the unit vector from 'vector'. For example:

double vector[3] = {-5, 4, -3};
double result[3];
unit(3, vector, result);
display_array(3, result);

-0.707107 0.565685 -0.424264
*/
void unit(int dim, double vector[dim], double result[dim]) {
   // Calculate the lenght of the 'vector'.
   double len = lenght(dim, vector); 
   // Check if the lenght of 'vector' is acceptable.
   assert (dim != 0);
   // Fill the 'result' with units.
   for (int i=0; i<dim; i++) 
      result[i] = vector[i] * (1/len); 
}

/* Sum the elements of 'vector1' and 'vector2'. For example: 

double vector1[3] = {-5, 4, -3};
double vector2[3] = {0, 7, 5};
double result[3];
add(3, vector1, vector2, result);
display_array(3, result);

-5.000000 11.000000 2.000000
*/
void add(int dim, double vector1[dim], double vector2[dim], 
         double result[dim]) {
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) 
      result[i] = vector1[i] + vector2[i]; 
}

/* Multiply the 'vector' with 'scaler'. For example: 

double vector[3] = {0, 7, 5};
double result[3];
scaler_mul(-4.8, 3, vector, result);
display_array(3, result);

-0.000000 -33.600000 -24.000000
*/
void scaler_mul(double scaler, int dim, double vector[dim], 
                double result[dim]) {
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) 
      result[i] = vector[i] * scaler; 
}

/* Measures the distance between 'vector1' and 'vector2'. 
For example:

double vector1[3] = {-5, 4, -3};
double vector2[3] = {-2, 7, 5};
double result = distance(3, vector1, vector2);
printf("%f\n", result);

9.055385
*/
double distance(int dim, double vector1[dim], double vector2[dim]){
   // Sum the distances between the points.
   double total = 0; double distance;
   for (int i=0; i<dim; i++) 
      // Find the distance between each points.
      total += pow(vector1[i] - vector2[i], 2);
   
   return sqrt(total);
}

/* Multiplies the 'vector1' and 'vector2' as dot. For example: 

double vector1[3] = {-5, 4, -3};
double vector2[3] = {-2, 7, 5};
double result = dot_mul(3, vector1, vector2);
printf("%f\n", result);

23.000000
*/
double dot_mul(int dim, double vector1[dim], double vector2[dim]){
   // Sum the multiplication of the pair of points. 
   float total = 0; 
   for (int i=0; i<dim; i++) 
      // Multiply the pairs of point with other.
      total += vector1[i] * vector2[i]; 

   return total; 
}

/* Return true, if there is Cauchy-Schwarz inequality. For 
example:

double vector1[3] = {-5, 4, -3};
double vector2[3] = {-2, 7, 5};
int result = iscs(3, vector1, vector2);
printf("%d\n", result);
1
*/
bool iscs(int dim, double vector1[dim], double vector2[dim]) {
   // Multiply 'vector1' and 'vector2' as dot.
   double mul1 = dot_mul(dim, vector1, vector2); 
   // Get the absolute value of 'mul1'.
   if (mul1 < 0) mul1 = -1 * mul1; 
   // Multiply 'vector1' with itself as dot.
   double mul2 = dot_mul(dim, vector1, vector1);
   // Multiply 'vector2' with itself as dot.
   double mul3 = dot_mul(dim, vector2, vector2);

   return (mul2 * mul3 >= mul1) ? true : false;
}

/* Return true, if there is triangular inequality. For example:

double vector1[3] = {-5, 4, -3};
double vector2[3] = {-2, 7, 5};
int result = istriangle(3, vector1, vector2);
printf("%d\n", result);
1
*/
bool istriangle(int dim, double vector1[dim], double vector2[dim]){
   // Sum the 'vector1' and 'vector2' with each other.
   double result[dim]; add(dim, vector1, vector2, result);
   // Find the lenght of 'result'.
   double len1 = lenght(dim, result); 
   // Find the lenght of 'vector1'.
   double len2 = lenght(dim, vector1); 
   // Find the lenght of 'vector2'.
   double len3 = lenght(dim, vector2);

   return (len2 + len3 >= len1) ? true : false;
}

/* Return true, if there is pythagorean inequality. For example:

double vector1[3] = {-5, 4, -3};
double vector2[3] = {-2, 7, 5};
int result = ispythag(3, vector1, vector2);
printf("%d\n", result);
0
*/
bool ispythag(int dim, double vector1[dim], double vector2[dim]){
   // Sum the 'vector1' and 'vector2' with each other.
   double result[dim]; 
   add(dim, vector1, vector2, result);
   // Find the lenght of 'result'.
   double slen1 = pow(lenght(dim, result), 2); 
   // Find the lenght of 'vector1'.
   double slen2 = pow(lenght(dim, vector1), 2); 
   // Find the lenght of 'vector2'.
   double slen3 = pow(lenght(dim, vector2), 2); 

   return (slen1 == slen2 + slen3) ? true : false;
}

/* Find angle between the 'vector1' and 'vector2'. 'method' 
argument accept 'decimal', 'radians', 'degrees'. For example:

double vector1[3] = {3, 4, -1};
double vector2[3] = {2, -1, 1};
double result;
result = angle("decimal", 3, vector1, vector2);
printf("%f\n", result);
result = angle("radians", 3, vector1, vector2);
printf("%f\n", result);
result = angle("degrees", 3, vector1, vector2);
printf("%f\n", result);

0.080064
1.490646
85.407751
*/
double angle(char* method, int dim, double vector1[dim], 
             double vector2[dim]) {
   // 'vector1' and 'vector2' must not be zero vector.
   assert (!iszeros(dim, vector1) && !iszeros(dim, vector2));
   // Check the 'method' is acceptable for that.
   assert (strcmp(method, "decimal") == 0 ||
           strcmp(method, "radians") == 0 ||
           strcmp(method, "degrees") == 0);
   // Multiply 'vector1' and 'vector2' as dot.
   double mul = dot_mul(dim, vector1, vector2);
   double pow1 = 0; double pow2 = 0;
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) pow1 += pow(vector1[i], 2);
   for (int i=0; i<dim; i++) pow2 += pow(vector2[i], 2);
   // Calculate the angle between vectors.
   float angle = mul / (sqrt(pow1) * sqrt(pow2)); 
   // Return the angle in appropriate form according to 'method'.
   if (strcmp(method, "decimal") == 0) return angle; 
   if (strcmp(method, "radians") == 0) return acos(angle);
   if (strcmp(method, "degrees") == 0) {
      double degrees = 57.2957795 * acos(angle); 
      return degrees;
   } 
}

/* Return true, if the 'vector1' and 'vector2' are steeps. For 
example: 

double vector1 = {-4, 0, 2, -2};
double vector2 = {2, 0, -1, 1};
double result = issteep(4, vector1, vector2);
printf("%d\n", result);
0
*/ 
bool issteep(int dim, double vector1[dim], double vector2[dim]) {
   // Can be used 'angle' method for this problem.
   double degrees = angle("degrees", dim, vector1, vector2);
   return ((float) degrees == 90.0) ? true : false;
}

/* Return true, if the 'vector1' and 'vector2' are parallel. For
example:

double vector1 = {-4, 0, 2, -2};
double vector2 = {2, 0, -1, 1};
double result = isparallel(4, vector1, vector2);
printf("%d\n", result);
1
*/ 
bool isparallel(int dim, double vector1[dim], double vector2[dim]){
   // Can be used 'angle' method for this problem.
   double degrees = angle("degrees", dim, vector1, vector2);
   return ((float) degrees == 180.0) ? true : false;
}

