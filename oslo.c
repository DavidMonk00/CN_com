#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
   int L;
   float p;
   int* array_slope;
   int* array_threshold;
} System;

int* createintArray(int length) {
   int* array;
   array = (int*)malloc(length*sizeof(int));
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

void drive(System* system) {
   System* s = system;
   s->array_slope[0]++;
}

void relax(System* system) {
   System* sys = system;
   int relaxed = 0;
   int s = 0;
   while (!relaxed) {

   }
}

int main(int argc, char** argv) {
   srand(time(NULL));
   System system;
   system.L = 8;
   system.p = 0.5;
   system.array_slope = createintArray(system.L);
   system.array_threshold = generateThresholdArray(system.L, system.p);
   drive(&system);
   printf("%d\n", system.array_slope[0]);

   free(system.array_slope);
   free(system.array_threshold);
   return 0;
}
