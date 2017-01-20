#include <iostream>
#include <time.h>
using namespace std;

class Grain {
   int z = 0;
   int threshold;
   float p;
public:
   Grain(float probability) {
      p = probability;
      float r = (float)rand()/(float)RAND_MAX;
      threshold = r < p ? 1 : 2;
   }
   int getZ() { return z; }
   int getThreshold() { return threshold; }
   void incrementSlope(int amount) { z = z + amount; }
   void decrementSlope(int amount) { z = z - amount; }
   bool slopeTest() { return z > threshold; }
   void resetThreshold() {
      float r = (float)rand()/(float)RAND_MAX;
      threshold = r < p ? 1 : 2;
   }
};

class System {
   int L;
   float p;
   Grain* array;
public:
   System(int length, float probability) {
      L = length;
      p = probability;
      array = new Grain[L];
   }
};

int main() {
   srand((unsigned)time(NULL));
   Grain g = Grain(0.5);
   cout << g.getThreshold() << endl;
   return 0;
}
