#ifndef _GEOMETRY_
#define _GEOMETRY_

struct Point
{
	double x, y;
	Point();
	double calc_distance(Point& p);
	void clear();
};


struct Triangle
{
	Point points[3];
	double area;
	Triangle(Point p1, Point p2, Point p3);
	Triangle();
	void calc_area();
	void set_coords(Point p1, Point p2, Point p3);
	void clear();
	void print_all();
};



#endif // !_GEOMETRY_
