#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Circle {
	double x_coord;
	double y_coord;
	double radius;
};

//
// reads the Circle and saves the user input values into the struct
//
Circle read_circle() {
	Circle c;
	double x, y, radius;
	cin >> x >> y >> radius;

	c.x_coord = x;
	c.y_coord = y;
	c.radius = radius;

	return c;
}

//
// this checks whether the circle overlaps and returns a boolean value
//
bool overlapped(Circle c1, Circle c2) {
	double dist = sqrt( pow( (c2.x_coord - c1.x_coord), 2) +  pow( (c2.y_coord - c1.y_coord), 2) ); 
	double sum_radius = c1.radius + c2.radius;

	if (dist - sum_radius <0) {
		return true;
	}

	return false;
}

int main (void) {
	bool status = true;
	Circle original = read_circle();

	// WORK WITH VECTOR
	std::vector<Circle> circ;

	while (status) {
		circ.push_back(read_circle());
		for (size_t i=0; i<circ.size(); i++) {
			if (circ[i].radius < 0) {
				status = false;
			}
		}
	}

	for (size_t i=0; i<circ.size()-1; i++) {
		if (overlapped(original, circ[i]) == true)
			cout << "overlapped\n";
		else
			cout << "not overlapped\n";
	}

	return 0;

}
