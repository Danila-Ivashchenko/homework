#ifndef _GEOMETRY_
#define _GEOMETRY_

struct Point
{
	double x, y;
};

struct Triangle
{
	Point vertex[3];
	double area;
};


double calc_distance(Point &p1, Point &p2);
double calc_area_triangle(Triangle& tr);

#endif

