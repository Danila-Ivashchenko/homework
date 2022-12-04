#pragma once
//#include "time.h"
#include <iostream>
#include <string>


using namespace std;

class Time {
	int seconds;
	int minuts;
	int hours;

public:
	Time() { seconds = 0; minuts = 0; hours = 0; };
	Time(int s, int m, int h) { seconds = s; minuts = m; hours = h; };

	friend ostream& operator << (ostream& out, const Time& time);
	friend class Date;
};


class Date {
	Time time;
	int day;
	int month;
	int year;
	int JDN;
	long double JD;
public:
	Date(int ajdn);
	Date(string timeStr, string format);
	Date(int dd, int mm, int yy);
	Date(int dd, int MM, int yy, int ss, int mm, int hh);
	int get_week_day();
	int jdn();
	long double jd();
	void set_from_jdn(const int& ajdn);
	void set_time(int ss, int mm, int hh);
	string format(const string& format);
	void print();
	Date next_easter();

	int operator - (const Date& adate) const;
	Date operator + (const int& anum) const;
	Date operator -(const int& anum) const;
	Date& operator +=(const int& anum);
	Date& operator -=(const int& anum);

	int get_day();
	int get_month();
	int get_year();
	int get_seconds();
	int get_minuts();
	int get_hours();

	operator int() { return jdn(); };
	friend ostream& operator << (ostream& out, const Date& date);
};
