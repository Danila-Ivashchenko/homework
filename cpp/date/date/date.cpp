#include <iostream>
#include "date.h"

using namespace std;

int main()
{
    string s = "21.11.2021";
    Date d(s), d2(30, 3, 2021);
    d.next_easter().print();
    return 1;
}
