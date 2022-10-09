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

ofstream& operator << (ofstream& out, const Triangle tr) {
	out << tr.points[0] << ' ' << tr.points[1] << ' ' << tr.points[2];
	return out;
};

ostream& operator << (ostream& out, const Triangle tr) {
	out << tr.points[0] << char(',') << ' ' << tr.points[1] << char(',') << ' ' << tr.points[2];
	return out;
};

/*void write_triangles(ofstream& out, Triangle* tr, int tr_nums) {
	for (int i = 0; i < tr_nums; i++)
		out << tr[i] << '\n';
};*/

void read_points(ifstream& input, Point* points, int points_num){
	for (int i = 0; i < points_num; i++) {
		input >> points[i];
	}
}


