#include "geometry.h"
#include <iostream>
#include <fstream>

using namespace std;

#ifndef _FILE_
#define _FILE_

istream& operator >> (istream& in, Point& p);
ostream& operator << (ostream& out,const Point& p);

ifstream& operator >> (ifstream& in, Point& p);
ofstream& operator << (ofstream& out, const Point& p);

#endif // !_FILE_

