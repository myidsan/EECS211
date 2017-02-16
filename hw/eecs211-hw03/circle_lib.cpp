#include "circle_lib.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

//
// reads the struct Circle
//
Circle read_circle()
{
    Circle c;
    double x,y,radius;
    cin >> x >> y >> radius;

    c.x = x;
    c.y= y;
    c.radius = radius;

    return c;
}

//
// returns a boolean whether two given circles overlap or not
//
bool overlapped(Circle c1, Circle c2)
{
    if (c1.radius < 0 || c2.radius <0 )
        throw runtime_error("One of the radius of the circle is a negative value.");

    double dist = sqrt( pow((c2.x - c1.x), 2) + pow((c2.y - c1.y), 2) );
    double sum_radius = c1.radius + c2.radius;

    if (dist - sum_radius < 0)
        return true;
    else
        return false;
}

