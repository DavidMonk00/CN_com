#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct {
   int L;
   float p;
   int* array_slope;
   int* array_threshold;
} System;

typedef struct {
   int** height;
   int** avalanches;
} Results;

int h = 0;

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

void writeFile(int** array, int length, int avalanche) {
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "./data/%Y%m%d%H%M%S", tm);
   char ext[64];
   if (avalanche) {
      sprintf(ext, "_avalanche.dat");
   } else {
      sprintf(ext, "_height.dat");
   }
   strcat(s,ext);
   FILE* f = fopen(s, "w");
   if (f == NULL) {
      printf("Error opening file.");
      exit(1);
   }
   int i; int j;
   for (i = 0; i < 7; i++) {
      for (j = 0; j < length; j++) {
         fprintf(f, "%d ", array[i][j]);
      }
      fprintf(f, "\n");
   }
   fclose(f);
}

void run(System* system, int n, Results* res) {
   int order = (int)log2(system->L) - 3;
   for (int i = 0; i < n; i++) {
      if (i % (n/100) == 0) {
         printf("%0.0f%%\n", ((float)i/(float)n)*100);
      }
      drive(system);
      res->avalanches[order][i] = relax(system);
      res->height[order][i] = h;
   }
}

int main(int argc, char** argv) {
   int n = (int)atof(argv[1]);
   int L[7] = {8,16,32,64,128,256,512};
   Results results;
   results.avalanches = create2DintArray(7, n);
   results.height = create2DintArray(7, n);
   srand(time(NULL));
   System* systems = (System*)malloc(7*sizeof(System));
   for (int i = 0; i < 7; i++) {
      h = 0;
      systems[i].L = L[i];
      systems[i].p = 0.5;
      systems[i].array_slope = createintArray(systems[i].L);
      systems[i].array_threshold = generateThresholdArray(systems[i].L, systems[i].p);
      run(&systems[i], n, &results);
   }

   writeFile(results.height, n, 0);
   writeFile(results.avalanches, n, 1);

   free(systems);
   free(results.avalanches);
   free(results.height);
   return 0;
}
