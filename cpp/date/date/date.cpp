#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    string s = "yyyy,mm,dd";
    string format = "ss:mm:hh:dd:MM:YYYY", format2 = "ss:mm:hh dd:MM:YY", value = "30:10:08:10:03:2003";
    Date d2(30, 3, 2021), d(value, format);
    cout << d.format(format2) << endl;
    cout << d2 << endl;

    cout << d2 - d << endl << endl;

    cout << d << endl;
    cout << d - 100 << endl;
    cout << d + 100 << endl << endl;

    d += 200;
    cout << d << endl;
    d -= 200;
    cout << d << endl << endl;

    cout << d.jdn() << endl;
    cout << d.jd() << endl;

    return 100;
}
