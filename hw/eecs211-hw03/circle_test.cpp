#include "circle_lib.h"

#include <UnitTest++/UnitTest++.h>
#include <stdexcept>

using namespace std;

TEST(OVERLAPPED)
{
    Circle c1;
      c1.x = 10;
      c1.y = 10;
      c1.radius = 10;
    Circle c2;
      c2.x = 30;
      c2.y = 10;
      c2.radius = 20;
    Circle c3;
      c3.x = 30;
      c3.y = 10;
      c3.radius = 10;
    CHECK_EQUAL(true, overlapped(c1,c2));
    CHECK_EQUAL(false, overlapped(c1,c3));
    CHECK_EQUAL(false, overlapped(c1,c3)); // tangential case
}

TEST(OVERLAPPED_ERROR)
{
    Circle c1;
      c1.x = 10;
      c1.y = 10;
      c1.radius = -10;
    Circle c2;
      c2.x = 30;
      c2.y = 10;
      c2.radius = 10;
    CHECK_THROW(overlapped(c1,c2), runtime_error);
}

