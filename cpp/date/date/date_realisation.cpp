#include "date.h"
#include "time.h"

/* Конструкторы класса */

Date::Date(int dd, int mm, int yy) {
	day = dd;
	month = mm;
	year = yy;
	time.seconds = 0;
	time.minuts = 0;
	time.hours = 0;
	JDN = jdn();
	JD = jd();
}

Date::Date(int dd, int MM, int yy, int ss, int mm, int hh){
	day = dd;
	month = MM;
	year = yy;
	time.seconds = ss;
	time.minuts = mm;
	time.hours = hh;
	JDN = jdn();
	JD = jd();
}

Date::Date(int ajdn)
{
	set_from_jdn(ajdn);
}

Date::Date(string timeStr, string format) {
	day = 0;
	month = 0;
	year = 0;
	time.seconds = 0;
	time.minuts = 0;
	time.hours = 0;
	int year_count = 0;
	int n_year = 0;
	int day_count = 0;
	int month_count = 0;
	int hour_count = 0;
	int minut_count = 0;
	int second_count = 0;
	int delta_year = 1;
	for (auto c : format) {
		if (c == 'y' || c == 'Y')
			year_count += 1;
		if (c == 'd' || c == 'D')
			day_count += 1;
		if (c == 'M')
			month_count += 1;
		if (c == 's')
			second_count += 1;
		if (c == 'm')
			minut_count += 1;
		if (c == 'h')
			hour_count += 1;
	}
	for (int i = 0; i < year_count - 1; i++) {
		delta_year *= 10;
	}

	int count = format.size();
	for (int i = 0; i < count; i++) {
		char c = format[i];
		if (c == 'y' || c == 'Y') {

			year += int(timeStr[i] - '0') * delta_year;
			delta_year /= 10;
		}
		if (c == 'd' || c == 'D') {
			if (day_count == 2)
				day += int(timeStr[i] - '0') * (10);
			else
				day += int(timeStr[i] - '0');
			day_count--;
		}
		if (c == 'M') {
			if (month_count == 2)
				month += int(timeStr[i] - '0') * (10);
			else
				month += int(timeStr[i] - '0');
			month_count--;
		}
		if (c == 's') {
			if (second_count == 2)
				time.seconds += int(timeStr[i] - '0') * (10);
			else
				time.seconds += int(timeStr[i] - '0');
			second_count--;
		}
		if (c == 'm') {
			if (minut_count == 2)
				time.minuts += int(timeStr[i] - '0') * (10);
			else
				time.minuts += int(timeStr[i] - '0');
			minut_count--;
		}
		if (c == 'h') {
			if (hour_count == 2)
				time.hours += int(timeStr[i] - '0') * (10);
			else
				time.hours += int(timeStr[i] - '0');
			hour_count--;
		}
	}
	JDN = jdn();
	JD = jdn();
}

/* Возврат значений */

int Date::get_day() {
	return day;
}

int Date::get_month() {
	return month;
}

int Date::get_year() {
	return year;
}

int Date::get_seconds() {
	return time.seconds;
}

int Date::get_minuts() {
	return time.minuts;
}

int Date::get_hours() {
	return time.hours;
}


/* Вывод даты */

string Date::format(const string& format) {
	string new_str = "";
	int year_count = 0;
	int n_year = 0;
	int day_count = 0;
	int month_count = 0;
	int minut_count = 0;
	int second_count = 0;
	int hour_count= 0;
	int delta_year = 1;
	for (auto c : format) {
		if (c == 'y' || c == 'Y')
			year_count += 1;
		if (c == 'd' || c == 'D')
			day_count += 1;
		if (c == 'M')
			month_count += 1;
		if (c == 's')
			second_count += 1;
		if (c == 'm')
			minut_count += 1;
		if (c == 'h')
			hour_count += 1;
	}
	if ((day_count != 0 || month_count != 0 || year_count != 0) && (day_count != 2 || month_count != 2 || year_count > 4) &&
		(second_count != 0 || minut_count != 0 || hour_count != 0) && (second_count != 2 || minut_count != 2 || hour_count != 2)) {
		return "bad_format";
	}
	for (int i = 0; i < year_count - 1; i++) {
		delta_year *= 10;
	}
	n_year += year % (delta_year * 10);
	for (auto c : format){
		if (c == 'd' || c == 'D') {
			if (day_count > 1)
				new_str += char(day / (10 * (day_count - 1)) + '0');
			else
				new_str += char(day % (10 * day_count) + '0');
			day_count--;
		} else if (c == 'M') {
			if (month_count > 1)
				new_str += char(month / (10 * (month_count - 1)) + '0');
			else
				new_str += char(month % (10 * month_count) + '0');
			month_count--;
		} else if (c == 'y' || c == 'Y') {
			if (year_count > 1)
				new_str += char(n_year / (delta_year)+'0');
			else
				new_str += char(n_year % 10 + '0');
			n_year %= delta_year;
			delta_year /= 10;
		} else if (c == 'm') {
			if (minut_count > 1)
				new_str += char(time.minuts / (10) + '0');
			else
				new_str += char(time.minuts % (10) + '0');
			minut_count--;
		} else if (c == 's') {
			if (second_count > 1)
				new_str += char(time.seconds / (10) + '0');
			else
				new_str += char(time.seconds % (10) + '0');
			second_count--;
		} else if (c == 'h') {
			if (hour_count > 1) {
				new_str += char(time.hours / 10 + '0');
			}
			else
				new_str += char(time.hours % 10 + '0');
			hour_count--;
		}
		else {
			new_str += c;
		}
	}
	return new_str;
}


void Date::print() {
	cout << day << " : " << month << " : " << year << endl;
}

/* Работа с датой в юлианском формате */

int Date::jdn() {
	int a = int((14 - month) / 12);
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;

	return day + int((153 * m + 2) / 5) + 365 * y + int(y / 4) - y / 100 + y / 400 - 32045;
}

long double Date::jd() {
	return JDN + double((double(time.hours) - 12) / 24) + double(time.minuts) / 1440 + double(time.seconds);
}

void Date::set_time(int ss, int mm, int hh) {
	time.seconds = ss;
	time.minuts = mm;
	time.hours = hh;
}

void Date::set_from_jdn(const int& ajdn) {
	int a = ajdn + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;
	day = e - (153 * m + 2) / 5 + 1;
	month = m + 3 - 12 * (m / 10);
	year = 100 * b + d - 4800 + m / 10;
	JDN = ajdn;
}

int Date::get_week_day() {
	return JDN % 7;
}

/* Операторы сложения / вычитания */

Date Date::operator +(const int& anum) const {
	Date new_date(JDN + anum);
	new_date.set_time(time.seconds, time.minuts, time.hours);
	return new_date;
}

Date Date::operator -(const int& anum) const {
	Date new_date(JDN - anum);
	new_date.set_time(time.seconds, time.minuts, time.hours);
	return new_date;
}

Date& Date::operator +=(const int& anum) {
	set_from_jdn(JDN + anum);
	return *this;
}

int Date::operator - (const Date& adate) const {
	return JDN - adate.JDN;
}

Date& Date::operator -=(const int& anum) {
	set_from_jdn(JDN - anum);
	return *this;
}


/* Нахождение дня пасхи */

Date Date::next_easter() {
	int pp = (19 * (year % 19) + 15) % 30;
	int fm = 21 + pp;
	int mm = 3;
	if (fm > 31) {
		fm -= 31;
		mm += 1;
	}
	int b = (2 * (year % 4) + 4 * (year % 7) + 6 * pp + 6) % 7;
	int f = pp + b;
	int ed, em = 3;
	if (f > 9) {
		ed = f - 9;
		em += 1;
	}
	else {
		ed = 22 + f;
	}

	Date easter(ed, em, year);
	return easter + 13;
}


/* Вывод даты */
ostream& operator << (ostream& out, const Date& date) {
	out << date.day / 10 << date.day % 10 << ":" << date.month / 10 << date.month % 10 << ":" << date.year << "T" << date.time;
	return out;
}


ostream& operator << (ostream& out, const Time& time) {
	out << time.seconds / 10 << time.seconds % 10 << ":" << time.minuts / 10 << time.minuts % 10 << ":" << time.hours / 10 << time.hours % 10;
	return out;
}

