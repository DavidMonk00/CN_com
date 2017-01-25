typedef struct {
   int L;
   float p;
   int* array_slope;
   int* array_threshold;
   int h;
} System;

typedef struct {
   int** height;
   int** avalanches;
} Results;

typedef struct {
   System system;
   int n;
   Results* res;
} InitParams;
