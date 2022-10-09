#include <iostream>
#include <fstream>


#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

using namespace std;


struct Point
{
	double x, y;
	Point() {
		x = y = 0;
	};
};

struct Triangle {
	Point points[3];
	double area;
	Triangle(Point& p1, Point& p2, Point& p3) {
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		area = 0;
	};
};

//double calc_distans(Point& p1, Point& p2);
//double calc_area(Triangle& tr);

#endif // !_GEOMETRY_H_

#pragma once
