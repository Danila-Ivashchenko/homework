#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
	double x, y;
	Point(double ax, double ay) : x(ax), y(ay) {};
	Point() : x(0), y(0) {};
	Point& operator = (const Point& apoint) {
		x = apoint.x;
		y = apoint.y;
		return *this;
	};
	friend ostream& operator <<(ostream& out, const Point& point) {
		out << point.x << " " << point.y;
		return out;
	};

	bool operator ==(const Point& p) {
		return x == p.x && y == p.y;
	}
	double vector_distance(const Point& p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
};


class Figure {
protected:
	int nodeCount;
	Point* points;
public:
	virtual void name() = 0;
	virtual void show_points() = 0;
	virtual double square() = 0;
	virtual double perimetr() = 0;
	friend double vector_lenght(const Point& p1, const Point& p2);
	//~Figure();
};


class Triangle : public Figure {
public:
	Triangle();
	Triangle(const Point& a, const Point& b, const Point& c);
	virtual void name();
	virtual void show_points();
	virtual double square();
	virtual double perimetr();
	friend Figure;
};

class Rectangle : public Figure {
public:
	Rectangle();
	Rectangle(const Point& a, const Point& b, const Point& c, Point& d);
	virtual void name();
	virtual void show_points();
	virtual double square();
	virtual double perimetr();
	friend Figure;
};

class Square : public Rectangle {
public:
	Square() : Rectangle() {};
	Square(const Point& a, const Point& b, const Point& c, Point& d) : Rectangle(a, b, c, d) {};
	virtual void name();
	friend Figure;

};

class Elips : public Figure {
protected:
	double r1, r2;
public:
	Elips();
	Elips(double ar, double ar1, const Point& ac);
	virtual void name();
	virtual void show_points();
	virtual double square();
	virtual double perimetr();
	friend Figure;

};


class Circle : public Elips {
public:
	Circle() : Elips() {};
	Circle(double ar, const Point& ac) : Elips(ar, ar, ac) {};
	virtual void name();
	virtual void show_points();
	virtual double perimetr();
	friend Figure;

};


class Polygon : public Figure {
public:
	Polygon();
	Polygon(vector <Point> a_points);
	virtual void name();
	virtual void show_points();
	virtual double square();
	virtual double perimetr();
};