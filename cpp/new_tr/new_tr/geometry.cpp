#include "geometry.h"
#include "file.h"
#include <math.h>

Point::Point() {
	x = 0;
	y = 0;
}

double Point::calc_distance(Point& p) {
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
};

void Point::clear() {
	x = y = 0;
};

Triangle::Triangle(Point p1, Point p2, Point p3) {
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	calc_area();
};

Triangle::Triangle() {
	area = 0;
};

void Triangle::set_coords(Point p1, Point p2, Point p3) {
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
};

void Triangle::clear() {
	area = 0;
	points[0].clear();
	points[1].clear();
	points[2].clear();
};

void Triangle::print_all() {
	for (auto point : points)
		cout << point << endl;
	cout << area << endl;
}

void  Triangle::calc_area() {
	double a = points[0].calc_distance(points[1]);
	double b = points[1].calc_distance(points[2]);
	double c = points[2].calc_distance(points[0]);
	double p = (a + b + c) / 2.0;
	if (p <= 0.0 || p <= a || p <= b || p <= c)
		area = 0;
	area = sqrt(p*(p-a)*(p-b)*(p-c));
};