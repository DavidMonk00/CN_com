/* 20161104
 * David Monk
 *
 * This header file contains basic functions used throughout the code.
 */

#include <math.h>

int length(double* array) {
   return sizeof(array)/sizeof(double);
}

/* Function: create2DArray
 * ------------------------
 * Creates a two-dimensional pointer array in the heap
 *
 * rows:    number of rows in array
 * columns: number of columns in array
 *
 * returns: empty 2D double pointer array.
 */
double** create2DArray(int rows, int columns) {
   double** array;
   array = malloc(rows*sizeof(double*));
   for (int i = 0; i < rows; i++) {
      array[i] = malloc(columns*sizeof(double));
   }
   return array;
}

/* Function: create1DArray
 * ------------------------
 * Creates a one-dimensional pointer array in the heap
 *
 * columns: number of columns in array
 *
 * returns: empty 1D double pointer array.
 */
double* create1DArray(int columns) {
   double* array;
   array = malloc(columns*sizeof(double));
   return array;
}

int** create2DintArray(int rows, int columns) {
   int** array;
   array = malloc(rows*sizeof(int*));
   for (int i = 0; i < rows; i++) {
      array[i] = malloc(columns*sizeof(int));
   }
   return array;
}

/* Function: create1DintArray
 * ------------------------
 * Creates a one-dimensional int pointer array in the heap
 *
 * columns: number of columns in array
 *
 * returns: empty 1D int pointer array.
 */
int* create1DintArray(int columns) {
   int* array;
   array = malloc(columns*sizeof(int));
   return array;
}
