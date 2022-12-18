#include "Figures.h"
#include <fstream>

#define M_PI 3.14159265358979323846

using namespace std;

double vector_lenght(const Point& p1, const Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//Figure::~Figure() {
//	delete points;
//}

/* Треугольник */

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
	nodeCount = 3;
	points = new Point[nodeCount];
	points[0] = a;
	points[1] = b;
	points[2] = c;
}

Triangle::Triangle() {
	nodeCount = 3;
	points = new Point[nodeCount];
	points[0] = Point(0, 0);
	points[1] = Point(0, 0);
	points[2] = Point(0, 0);
}

void Triangle::name() {
	cout << "Triangle" << endl;
}

void Triangle::show_points() {
	for (int i = 0; i < nodeCount; i++)
		cout << points[i] << ", ";
	cout << endl;
}

double Triangle::square() {
	return abs((points[1].x - points[0].x) * (points[2].y - points[0].y) - (points[2].x - points[0].x) * (points[1].y - points[0].y)) / 2;
}

double Triangle::perimetr() {
	return vector_lenght(points[0], points[1]) + vector_lenght(points[1], points[2]) + vector_lenght(points[2], points[0]);
}

/* Прямоугольник */

Rectangle::Rectangle() {
	nodeCount = 4;
	points = new Point[nodeCount];
	for (int i = 0; i < nodeCount; i++)
		points[i] = Point(0, 0);
}

Rectangle::Rectangle(const Point& a, const Point& b, const Point& c, Point& d) {
	nodeCount = 4;
	points = new Point[nodeCount];
	points[0] = a;
	points[1] = b;
	points[2] = c;
	points[3] = d;
	//if (a.x != b.x || a.y != d.y || c.y != b.y || c.x != d.x)
	//	throw exception();
}

void Rectangle::name() {
	cout << "Rectangle" << endl;
}

void Rectangle::show_points() {
	for (int i = 0; i < nodeCount; i++)
		cout << points[i] << ", ";
	cout << endl;
}

double Rectangle::square() {
	double a_line = sqrt((points[1].x - points[0].x) * (points[1].x - points[0].x) + (points[1].y - points[0].y) * (points[1].y - points[0].y));
	double b_line = sqrt((points[2].x - points[1].x) * (points[2].x - points[1].x) + (points[2].y - points[1].y) * (points[2].y - points[1].y));

	return a_line * b_line;
}

double Rectangle::perimetr() {
	return 2 * (vector_lenght(points[0], points[1]) + vector_lenght(points[1], points[2]));
}

/* Квадрат */

void Square::name(){
	cout << "Square" << endl;
}

/* Элипс */

Elips::Elips() {
	nodeCount = 0;
}

Elips::Elips(double ar, double ar1, const Point & ac) {
	nodeCount = 1;
	points = new Point[nodeCount];
	points[0] = ac;
	r1 = ar;
	r2 = ar1;
};

void Elips::name() {
	cout << "Elips" << endl;
}

void Elips::show_points() {
	cout << "radius 1 - " << r1 << endl;
	cout << "radius 2 - " << r2 << endl;
	cout << "center - " << points[0] << endl;
}

double Elips::square() {
	return r1 * r2 * M_PI;
}

double Elips::perimetr() {
	return 2 * M_PI * sqrt((r1 * r1 + r2 * r2) / 2);
}

/* Круг */

void Circle::name() {
	cout << "Circle" << endl;
}

void Circle::show_points() {
	cout << "radius - " << r1 << endl;
	cout << "center - " << points[0] << endl;

}

double Circle::perimetr() {
	return 2 * M_PI * r1;
}

/* Многоугольник */

//Polygon::Polygon() {
//	nodeCount = 0;
//}
//
//Polygon::Polygon(const string& filename) {
//	ifstream in(filename);
//	in >> nodeCount;
//	points = new Point[nodeCount];
//	for (int i = 0; i < nodeCount; i++) {
//		in >> points[i].x >> points[i].y;
//	}
//}


