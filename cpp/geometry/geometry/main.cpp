#include <iostream>
#include "Figures.h"

int main()
{
    Point a(-1, -3), b(3, 4), c(5, -5);
    Point a1(1, 1), b1(1, 4), c1(5, 4), d1(5, 1);
    Point c2(4, 4), d2(4, 1);
    Triangle tr1(a, b, c);
    Rectangle rt1(a1, b1, c1, d1);
    Square sq1(a1, b1, c2, d2);
    Elips el1(2, 4, Point(5, 5));
    Circle cl1(4.12, Point(5, 5));

    tr1.name();
    tr1.show_points();
    cout << "S = " << tr1.square() << endl;
    cout << "P = " << tr1.perimetr() << endl << endl;

    rt1.name();
    rt1.show_points();
    cout << "S = " << rt1.square() << endl;
    cout << "P = " << rt1.perimetr() << endl << endl;


    sq1.name();
    sq1.show_points();
    cout << "S = " << sq1.square() << endl;
    cout << "P = " << sq1.perimetr() << endl << endl;

    el1.name();
    el1.show_points();
    cout << "S = " << el1.square() << endl;
    cout << "P = " << el1.perimetr() << endl << endl;

    cl1.name();
    cl1.show_points();
    cout << "S = " << cl1.square() << endl;
    cout << "P = " << cl1.perimetr() << endl << endl;

    cout << tr1.square() << " " << rt1.square() << " " << sq1.square();
    return 10;
}
