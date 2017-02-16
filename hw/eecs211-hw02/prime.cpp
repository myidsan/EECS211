#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int n) {
   int i; int wall = sqrt(n);

   for (i=2; i<=wall; i++) {
      if (n%i == 0)
         return false;
   }

   return true;

}

int main() {
   int num; int i;
   cin >> num;

   for (i=2; i<num; i++) {
      if (is_prime(i) == true) {
         cout << i << '\n';
      }
   }

   return 0;
}


