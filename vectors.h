/* Vector operations in ALAT (Advanced Linear Algebra Toolkit) 

Vectors are used in so many area as matrices. So I've written this
source file. I hope, it will be useful...

+ lenght()
+ isequal()
+ iszero()
+ unit()
+ add()
+ scaler_mul()
+ distance()
+ dot_mul()
+ iscs()
+ istriangle()
+ ispythag()
+ angle()
+ isorthonal()
+ isparallel()

*/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* Calculate the lenght of any vector. */
float lenght(int dim, float vector[dim]) {
   float pow = 0; // firstly, get the pow of all points
   for (int i=0; i<dim; i++) pow += vector[i] * vector[i];
   return sqrt(pow); // Ana then, get squares and return result
}

/* Check if given two vectors are equal or not. */
bool isequal(int dim, float vector1[dim], float vector2[dim]) {
   int notsame = 0; // count the non-same points
   // Iterate the 'vector1' and 'vector2'.
   for (int i=0; i<dim; i++) 
   if (vector1[i] != vector2[i]) notsame ++;
   if (notsame != 0) return false; else return true;
}

/* Check if given two vector is zero vector or not. */
bool iszero(int dim, float vector[dim]) {
   int zero = 0; // count the zero points
   for (int i=0; i<dim; i++) // iterate the 'vector' points
   if (vector[i] == 0) zero ++; // indicate if point is zero
   if (zero == dim) return true; else return false;
}

/* Finds unit vector of any vector. */
void unit(int dim, float vector[dim], float result[dim]) {
   float len = lenght(dim, vector); // get the lenght of 'vector'
   if (len == 0) { // check if lenght of 'vector' is zero
      puts("VectorError: Lenght of 'vector' is zero.");
      exit(EXIT_FAILURE);
   }
   for (int i=0; i<dim; i++) // iterate the 'vector' points
   result[i] = vector[i] * (1/len); 
}

/* Sum up the 'vector1' and 'vector2' onto ''result. */
void add(int dim, float vector1[dim], float vector2[dim], 
         float result[dim]) {
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) result[i] = vector1[i] + vector2[i]; 
}

/* Multiplies a 'scaler' and 'vector' and save the onto 'result'. */
void scaler_mul(float scaler, int dim, float vector[dim], 
                float result[dim]) {
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) result[i] = vector[i] * scaler; 
}

/* Measures the distance between 'vector1' and 'vector2'. */
float distance(int dim, float vector1[dim], float vector2[dim]) {
   float distances = 0; // distances between point of vectors
   for (int i=0; i<dim; i++) { // iterate the vectors
      float distance = vector1[i] - vector2[i]; // get distance
      distances += pow(distance, 2); // sum up 'distance'.
   }
   return sqrt(distances); // get square root of collected distances
}

/* Multiplies the 'vector1' and 'vector2' onto 'result' as dot. */
float dot_mul(int dim, float vector1[dim], float vector2[dim]) {
   float dot = 0; // dot multiplications
   for (int i=0; i<dim; i++) // iterate the 'vector1' and 'vector2'
   dot += vector1[i] * vector2[i]; // collect multiplied points 
   return dot; 
}

/* Return true, if there is Cauchy-Schwarz inequality. */
bool iscs(int dim, float vector1[dim], float vector2[dim]) {
   // Multiply 'vector1' and 'vector2' as dot.
   float mul1 = dot_mul(dim, vector1, vector2); 
   if (mul1 < 0) mul1 = -1 * mul1; // get absolute value of 'mul'
   // Multiply 'vector1' with itself as dot.
   float mul2 = dot_mul(dim, vector1, vector1);
   // Multiply 'vector2' with itself as dot.
   float mul3 = dot_mul(dim, vector2, vector2);
   if (mul2 * mul3 >= mul1) return true; else return false; 
}

/* Return true, if there is triangular inequality. */
bool istriangle(int dim, float vector1[dim], float vector2[dim]) {
   // Collect the 'vector1' and 'vector2' onto 'result'.
   float result[dim]; add(dim, vector1, vector2, result);
   float len1 = lenght(dim, result); // lenght of 'result' 
   float len2 = lenght(dim, vector1); // lenght of 'vector1'
   float len3 = lenght(dim, vector2); // lenght of 'vector2'
   if (len2 + len3 >= len1) return true; else return false;
}

/* Return true, if there is pythagorean inequality. */
bool ispythag(int dim, float vector1[dim], float vector2[dim]) {
   // Collect the 'vector1' and 'vector2' onto 'result'.
   float result[dim]; add(dim, vector1, vector2, result);
   float len1 = lenght(dim, result); // lenght of 'result' 
   float len2 = lenght(dim, vector1); // lenght of 'vector1'
   float len3 = lenght(dim, vector2); // lenght of 'vector2'
   if (pow(len1, 2) == pow(len2, 2) + pow(len3, 2)) return true;
   else return false;
}

/* Find angle between the 'vector1' and 'vector2'. 'method' 
argument accept 'decimal', 'radians', 'degrees'. */
float angle(char* method, int dim, float vector1[dim], 
            float vector2[dim]) {
   // Any vector must not be zero vector.
   if (iszero(dim, vector1) || iszero(dim, vector2)) {
      puts("VectorError: Vector/s must not be zero vectors.");
      exit(EXIT_FAILURE);
   }
   // Multiply 'vector1' and 'vector2' as dot.
   float mul = dot_mul(dim, vector1, vector2);
   float pow1 = 0; float pow2 = 0;
   // Iterate the 'vector1' and 'vector2' points.
   for (int i=0; i<dim; i++) pow1 += pow(vector1[i], 2);
   for (int i=0; i<dim; i++) pow2 += pow(vector2[i], 2);
   // Calculate the angle between vectors.
   float angle = mul / (sqrt(pow1) * sqrt(pow2));
   // Return the angle in appropriate form according to 'method'.
   if (strcmp(method, "decimal") == 0) return angle;
   else if (strcmp(method, "radians") == 0) return acos(angle);
   else if (strcmp(method, "degrees") == 0) {
      float degrees = 57.2957795 * acos(angle); return degrees;
   } else { 
      puts("VectorError: Inconsistent 'method' parameter.");
      exit(EXIT_FAILURE);
   }
}

/* Return true, if the 'vector1' and 'vector2' are steeps. */ 
bool issteep(int dim, float vector1[dim], float vector2[dim]) {
   // Can be used 'angle' method for this problem.
   float degrees = angle("degrees", dim, vector1, vector2);
   if (degrees == 90.0) return true; else return false;
}

/* Return true, if the 'vector1' and 'vector2' are parallel. */ 
bool isparallel(int dim, float vector1[dim], float vector2[dim]) {
   // Can be used 'angle' method for this problem.
   float degrees = angle("degrees", dim, vector1, vector2);
   if (degrees == 180.0) return true; else return false;
}

