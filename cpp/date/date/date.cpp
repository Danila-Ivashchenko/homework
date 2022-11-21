#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    string s = "yyyy,mm,dd";
    Date d2(30, 3, 2021);
    cout << d2.format(s);
    return 1;
}
