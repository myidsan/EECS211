#include "circle_lib.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  Circle C1;
  Circle C2;
  C2.radius = 1;

  C1 = read_circle();
  C2 = read_circle();

  while (C2.radius >= 0) {
    if (overlapped(C1, C2) == true) {
      cout << "overlapped\n";
    } else {
      cout << "not overlapped\n";
    }
    C2 = read_circle();
  }

  return 0;
}
