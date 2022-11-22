#pragma once
#include "date.h"

using namespace std;

class Time {
	int seconds;
	int minuts;
	int hours;

public:
	Time() { seconds = 0; minuts = 0; hours = 0; };
	Time(int s, int m, int h) { seconds = s; minuts = m; hours = h; };
	Time(string timeStr);


	friend class Date;
	friend ostream& operator << (ostream& out, const Time& time);
};


Time::Time(string timeStr) {

}


ostream& operator << (ostream& out, const Time& time) {
	out << time.seconds / 10 << time.seconds % 10 << ":" << time.hours / 10 << time.hours % 10 << ":" << time.hours / 10 << time.hours % 10;
	return out;
}