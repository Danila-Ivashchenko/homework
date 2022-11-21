#pragma once
#include <iostream>
#include <string>

using namespace std;

class Date {
	int day;
	int month;
	int year;
	double jd;
	int JDN;
public:
	Date(int ajdn);
	Date(string ddmmyy);
	Date(int dd, int mm, int yy);
	Date();
	int get_week_day();
	int jdn();
	void set_from_jdn(const int& ajdn);
	void print(const string& format);
	void print();
	Date next_easter();

	int operator - (const Date& adate) const;
	Date operator + (const int& anum) const;
	Date& operator +=(const int& anum);
	Date& operator -=(const int& anum);

	operator int() { return jdn(); };
};
