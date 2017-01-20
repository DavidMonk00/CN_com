#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
   int L;
   float p;
   int* array_slope;
   int* array_threshold;
} System;

int h = 0;

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
   h++;
}

int relax(System* system) {
   System* sys = system;
   int* slope = sys->array_slope;
   int* threshold = sys->array_threshold;
   int L = sys->L;
   int relaxed = 0;
   int s = 0;
   while (!relaxed) {
      relaxed = 1;
      int i = 0;
      while (i < sys->L) {
         if (i == 0){
            if (slope[0] > threshold[0]){
               slope[0] = slope[0] - 2;
               slope[1]++;
               float r = (float)rand()/(float)RAND_MAX;
               threshold[0] = r < sys->p ? 1 : 2;
               relaxed = 0;
               s++;
               h--;
            }
            i++;
         }
         else if (i == L-1) {
            if (slope[L-1] > threshold[L-1]){
               slope[L-1]--;
               slope[L-2]++;
               float r = (float)rand()/(float)RAND_MAX;
               threshold[L-1] = r < sys->p ? 1 : 2;
               relaxed = 0;
               s++;
               i--;
            } else {
               i++;
            }
         }
         else {
            if (slope[i] > threshold[i]) {
               slope[i] = slope[i] - 2;
               slope[i+1]++;
               slope[i-1]++;
               float r = (float)rand()/(float)RAND_MAX;
               threshold[i] = r < sys->p ? 1 : 2;
               relaxed = 0;
               s++;
               i--;
            } else {
               i++;
            }
         }
      }
   }
   return s;
}

void writeFile(int* array, int length) {
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "./data/%Y%m%d%H%M%S.dat", tm);
   FILE* f = fopen(s, "w");
   if (f == NULL) {
      printf("Error opening file.");
      exit(1);
   }
   int i;
   for (i = 0; i < length; i++) {
      fprintf(f, "%d ", array[i]);
   }
   fprintf(f, "\n");
   fclose(f);

}

int main(int argc, char** argv) {
   srand(time(NULL));
   System system;
   system.L = atoi(argv[1]);
   int n = atoi(argv[2]);
   system.p = 0.5;
   system.array_slope = createintArray(system.L);
   system.array_threshold = generateThresholdArray(system.L, system.p);
   int* height = createintArray(n);
   for (int i = 0; i < n; i++) {
      drive(&system);
      relax(&system);
         height[i] = h;
   }
   writeFile(height, n);

   free(system.array_slope);
   free(system.array_threshold);
   return 0;
}
