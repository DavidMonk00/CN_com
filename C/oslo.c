#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "structs.h"
#include "backgroundfunctions.h"

int fallen = 0;

void drive(System* system) {
   System* s = system;
   s->array_slope[0]++;
   s->h++;
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
      while (i < L) {
         if (i == 0){
            if (slope[0] > threshold[0]){
               slope[0] = slope[0] - 2;
               slope[1]++;
               float r = (float)rand()/(float)RAND_MAX;
               threshold[0] = r < sys->p ? 1 : 2;
               relaxed = 0;
               s++;
               sys->h--;
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
               if (fallen == 0) {
                  fallen = 1;
               }
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

void writeFile(int** array, int length, int states, int avalanche) {
   int l = (int)log10((double)length);
   int x = length/pow(10,l);
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "./data/%Y%m%d%H%M%S", tm);
   char ext[64];
   if (avalanche) {
      sprintf(ext, "_%de%d_%d_avalanche.dat", x,l, states);
   } else {
      sprintf(ext, "_%de%d_%d_height.dat", x,l, states);
   }
   strcat(s,ext);
   FILE* f = fopen(s, "w");
   if (f == NULL) {
      printf("Error opening file.");
      exit(1);
   }
   int i; int j;
   for (i = 0; i < states; i++) {
      for (j = 0; j < length; j++) {
         fprintf(f, "%d ", array[i][j]);
      }
      fprintf(f, "\n");
   }
   fclose(f);
}

void* run(void* init) {
   fallen = 0;
   InitParams* params = (InitParams*)init;
   int order = (int)log2(params->system.L) - 3;
   printf("Starting sytem L = %d\n", params->system.L);
   for (int i = 0; i < params->n; i++) {
      if (i % (params->n/10) == 0) {
         printf("%0.0f%%\n", ((float)i/(float)params->n)*100);
      }
      drive(&params->system);
      params->res->avalanches[order][i] = relax(&params->system);
      if (fallen == 1) {
         printf("First grain fell at: %d height was: %d\n", i, params->system.h);
         fallen++;
         //break;
      }
      params->res->height[order][i] = params->system.h;
   }
   printf("100%%\n");
   return NULL;
}

int main(int argc, char** argv) {
   int n = (int)atof(argv[1]);
   int states = (int)atof(argv[2]);

   /*pthread_t thread[states];
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);*/

   Results results;
   results.avalanches = create2DintArray(states, n);
   results.height = create2DintArray(states, n);
   srand(time(NULL));
   InitParams init[states];
   for (int i = 0; i < states; i++) {
      int L = (int)pow(2,i+3);
      System sys;
      sys.L = L;
      sys.p = 0.5;
      sys.h = 0;
      sys.array_slope = createintArray(L);
      sys.array_threshold = generateThresholdArray(L, sys.p);
      init[i].system = sys;
      init[i].n = n;
      init[i].res = &results;
   }
   printf("%s\n", "Running...");
   //void* status;
   for (int i = 0; i < states; i++) {
      //pthread_create(&thread[i], &attr, run, (void*)&init[i]);
      run((void*)&init[i]);
   }
   //for (int i = 0; i < states; i++) {
   //   pthread_join(thread[i],&status);
   //}
   printf("%s\n", "Writing to file...");
   writeFile(results.height, n, states, 0);
   writeFile(results.avalanches, n, states, 1);


   free(results.avalanches);
   free(results.height);
   return 0;
}
