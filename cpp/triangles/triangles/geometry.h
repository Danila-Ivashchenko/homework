#include <iostream>
#include <fstream>

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

std::istream& operator >>(std::istream& in, Point& p);
std::ostream& operator <<(std::ostream& out, const Point& p);

std::ofstream& operator << (std::ostream &out, Point& p);
std::ifstream& operator >> (std::ifstream &in, Point p);


struct Point
{
	double x, y;
	Point() {
		x = y = 0;
	};
};

#endif // !_GEOMETRY_H_

#pragma once
