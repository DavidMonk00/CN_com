int* createintArray(int length) {
   int* array;
   array = (int*)malloc(length*sizeof(int));
   return array;
}

int** create2DintArray(int rows, int columns) {
   int** array;
   array = (int**)malloc(rows*sizeof(int*));
   for (int i = 0; i < rows; i++) {
      array[i] = (int*)malloc(columns*sizeof(int));
   }
   return array;
}

int* generateThresholdArray(int length, float probability) {
   int* array = createintArray(length);
   for (int i = 0; i < length; i++) {
         float r = (float)rand()/(float)RAND_MAX;
         array[i] = r < probability ? 1 : 2;
   }
   return array;
}
