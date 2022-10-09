#include "geometry.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;


//
//double calc_distans(Point& p1, Point& p2) {
//	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
//};
//
//double calc_area(Triangle& tr) {
//	double a = calc_distans(tr.points[0], tr.points[1]);
//	double b = calc_distans(tr.points[1], tr.points[2]);
//	double c = calc_distans(tr.points[2], tr.points[0]);
//	double p = (a + b + c) / 2;
//	return sqrt(p * (p - a) * (p - b) * (p - c));
//};
