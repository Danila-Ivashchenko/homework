#include "geometry.h"
#include <fstream>
#include <iostream>

std::istream& operator >>(std::istream& in, Point& p) {
	return in >> p.x >> p.y;
}
std::ostream& operator <<(std::ostream& out, const Point& p) {
	return out << p.x << ' ' << p.y;
};
