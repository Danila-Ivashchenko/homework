#include "date.h"



/* Конструкторы класса */

Date::Date(int dd, int mm, int yy) {
	day = dd;
	month = mm;
	year = yy;
	JDN = jdn();
}

Date::Date(int ajdn)
{
	set_from_jdn(ajdn);
}

Date::Date(string ddmmyy) {
	day = int(ddmmyy[0] - '0') * 10 + int(ddmmyy[1] - '0');
	month = int(ddmmyy[3] - '0') * 10 + int(ddmmyy[4] - '0');
	year = int(ddmmyy[6] - '0') * 1000 + int(ddmmyy[7] - '0') * 100 + int(ddmmyy[8] - '0') * 10 + int(ddmmyy[9] - '0');
	JDN = jdn();
}

/* Вывод даты */

//Вывод в формате не доделан
//void Date::print(const string& format) {
//	string new_str = "";
//	int year_count = 0;
//	int day_count = 0;
//	int month_count = 0;
//	for (auto c : format) {
//		if (c == 'y' || c == 'Y')
//			year_count += 1;
//		if (c == 'd' || c == 'D')
//			day_count += 1;
//		if (c == 'm' || c == 'M')
//			month_count += 1;
//	}
//
//	for (auto c : format){
//		if (c == 'd' || c == 'D') {
//			day_count -= 1;
//			new_str += char(day / (10 * )
//		}
//	}
//	cout << day << " : " << month << " : " << year << endl;
//}

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
	cout << fm << " " << mm << " " << year << endl;
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