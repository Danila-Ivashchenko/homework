#include "geometry.h"
#include <cmath>

using namespace std;

double calc_distance(Point& p1, Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
};
double calc_area_triangle(Triangle& tr) {
	Point* v = tr.vertex;
	double d1 = calc_distance(v[0], v[1]);
	double d2 = calc_distance(v[1], v[2]);
	double d3 = calc_distance(v[2], v[0]);
	double p = (d1 + d2 + d3) / 2;
	return sqrt(p * (p - d1) * (p - d2) * (p - d3));
};