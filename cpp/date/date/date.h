#pragma once
#include <iostream>
#include <string>
#include "time.h"

using namespace std;

class Date {
	int day;
	int month;
	int year;
	double jd;
	int JDN;
	Time time;
public:
	Date(int ajdn);
	Date(string timeStr, string format);
	Date(int dd, int mm, int yy);
	Date();
	int get_week_day();
	int jdn();
	void set_from_jdn(const int& ajdn);
	string format(const string& format);
	void print();
	Date next_easter();

	int operator - (const Date& adate) const;
	Date operator + (const int& anum) const;
	Date& operator +=(const int& anum);
	Date& operator -=(const int& anum);

	operator int() { return jdn(); };
	friend ostream& operator << (ostream& out, const Date& date);
};

