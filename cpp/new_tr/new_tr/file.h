#include "geometry.h"
#include <iostream>
#include <fstream>

using namespace std;

#ifndef _FILE_
#define _FILE_

void read_points(ifstream& input, Point* points, int points_num);

//void write_triangles(ofstream& out, Triangle* tr, int tr_nums);

istream& operator >> (istream& in, Point& p);

ostream& operator << (ostream& out, const Point& p);

ifstream& operator >> (ifstream& in, Point& p);

ofstream& operator << (ofstream& out, const Triangle tr);

ostream& operator << (ostream& out, const Triangle tr);

#endif // !_FILE_

