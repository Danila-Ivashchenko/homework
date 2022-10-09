#include "file.h"
#include "geometry.h"
#include <iostream>
#include <fstream>

using namespace std;

istream& operator >> (istream& in, Point& p) {
	in >> p.x >> p.y;
	return in;
};

ostream& operator << (ostream& out, const Point& p) {
	out << p.x << ' ' << p.y;
	return out;
};

ifstream& operator >> (ifstream& in, Point& p) {
	in >> p.x >> p.y;
	return in;
};
ofstream& operator << (ofstream& out, const Point& p) {
	out << p.x << ' ' << p.y;
	return out;
};
