#include <iostream>
#include "class.h"
#include "test.h"

using namespace std;

Rational sqr_t(Rational& n)
{
    Rational s = 0;
    while (s * s < n) {
        s += 1;
    }
    if (s * s == n)
        return s;
    Rational xn = ((s - 1) + n / (s - 1)) / 2;
    int max = INT_MAX;
    while (xn.numer / xn.denom < (max / xn.denom - n.numer / n.denom / xn.numer) / xn.numer) {
        xn = (xn + n / xn) / 2;
    }
    return xn;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    Rational a, b, c;
    while (1 == 1) {
        cout << "Введите a: ";
        cin >> a;
        if (a == 0)
            break;
        cout << "Введите b: ";
        cin >> b;
        cout << "Введите c: ";
        cin >> c;
        Rational d = b * b - 4 * a * c;
        if (d < 0) {
            cout << "Дискриминант: " << d << " меньше нуля" << endl;
            continue;
        }
        else if (d == 0) {
            cout << a << "x^2" << " + " << "(" << b << ")x + " << c << " = 0" << endl;
            cout << "D = " << d << "sqrt(D) = " << 0 << endl;
            Rational xf = (-b) / 2 / a;
            cout << "x = " << xf << endl;
        }
        else {
            Rational qd = sqrt(d);
            cout << a << "x^2" << " + " << "(" << b << ")x + " << c << " = 0" << endl;
            cout << "D = " << d << " sqrt(D) = " << qd << endl;
            Rational xf = (-b + qd) / 2 / a, xs = (-b - qd) / 2 / a;
            cout << "x1 = " << xf << " " << "x2 = " << xs << endl;
        }
    }
    
    return 101;
}