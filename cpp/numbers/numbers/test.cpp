#include "test.h"
#include "class.h"
#include <iostream>

using namespace std;

void test_engine(Rational a, Rational b) {
    cout << "a = " << a << ' ' << "b = " << b << endl;
    cout << "-a = " << -a << ' ' << "-b = " << -b << endl << endl;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a == -b: " << (a == -b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a > b: " << (a == b) << endl;
    cout << "a <= b: " << (a == b) << endl;
    cout << "a >= b: " << (a == b) << endl;
    cout << "a >= -b: " << (a == -b) << endl << endl;

    cout << "++a = " << ++a << endl;
    cout << "a++ = " << a++ << ' ' << a << endl;
    cout << "--a = " << --a << endl;
    cout << "a-- = " << a-- << ' ' << a << endl << endl;

    cout << "a + 2 = " << a + 2 << endl;
    cout << "a - 2 = " << a - 2 << endl;
    cout << "a * (-8) = " << a * -8 << endl;
    cout << "a / (-8) = " << a / -8 << endl << endl;

    a += 2;
    cout << "a += 2, a = " << a << endl;
    a -= 2;
    cout << "a -= 2, a = " << a << endl;
    a *= 2;
    cout << "a *= 2, a = " << a << endl;
    a /= 2;
    cout << "a /= 2, a = " << a << endl << endl;

    a.flip();
    cout << "a^-1 = " << a << endl << endl;
    a.flip();

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl << endl;

    cout << "5 + a = " << 5 + a << endl;
    cout << "5 - a = " << 5 - a << endl;
    cout << "5 * a = " << 5 * a << endl;
    cout << "5 / a = " << 5 / a << endl << endl;
}
