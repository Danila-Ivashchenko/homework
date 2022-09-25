#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int get_data_int(string str, int pos, int size) {
	int data = 0;
	int n = 1;
	for (int i = 1; i < size; i++) {
		n *= 10;
	}
	string buf = str.substr(pos, size);
	for (int i = 0; i < buf.size(); i++) {
		data += int(buf[i] - '0') * n;
		n /= 10;
	}
	return data;
}

int get_count_of_month(int month, int year) {

	switch (month)
	{
	case 1:
		if (year == 2017)
			return 0;
		return 31;
		break;
	case 2:
		if (year == 2017)
			return 0;
		if (year % 4 == 0)
			return 29;
		else
			return 28;
	case 3:
		return 31;
		break;
	case 4:
		return 30;
		break;
	case 5:
		return 31;
		break;
	case 6:
		return 30;
		break;
	case 7:
		return 31;
		break;
	case 8:
		return 31;
		break;
	case 9:
		return 30;
		break;
	case 10:
		return 31;
		break;
	case 11:
		return 30;
		break;
	case 0:
		return 0;
		break;
	default:
		break;
	}
}

double convert(string str) {
	bool point = false;
	bool negative = false;
	double result = 0;
	double n = 0.1;

	for (int i = 1; i < str.length(); i++) {
		if (str[i] != '.')
			n *= 10;
		else
			break;
	}

	if (str[0] == '-')
		negative = true;
	else {
		result += int(str[0] - '0') * n * 10;
	}

	for (int i = 1; i < str.length(); i++) {
		if (!point) {
			if (str[i] != '.') {
				result += int(str[i] - '0') * n;
				n /= 10;
			}
			else {
				point = true;
			}
		}
		else {
			result += double(str[i] - '0') * n;
			n /= 10;
		}
	}
	if (negative)
		return 0 - result;
	else
		return result;
}


double find_el(string str) {
	string buf = "";
	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ' && str[i] != '\t')
			buf += str[i];
		else {
			if (buf == "")
				continue;
			count += 1;
			if (count == 5)
				return convert(buf);
			buf = "";
		}
	}
	return 0;
}


int count_bytes_to_move(int year, int month, int day, int step) {
	int day_in_months = 0;
	day -= 1;
	month -= 1;
	if (month > 0)
		while (month > 0) {
			//cout << "что " << get_count_of_month(month, year) << endl;
			day_in_months += get_count_of_month(month, year);
			month -= 1;
		}

	return (day + day_in_months) * (4 * sizeof(int) + sizeof(double)) * (86400 / step);
}

int get_time(string str) {
	int hours = get_data_int(str, 9, 2);
	int minuts = get_data_int(str, 11, 2);
	return get_data_int(str, 13, 2) + minuts * 60 + hours * 60 * 60;
}

char* set_time(int seconds) {
	static char time[8];
	int hours = seconds / 3600;
	seconds %= 3600;
	int minuts = seconds / 60;
	seconds %= 60;
	time[0] = char(hours / 10) + '0'; time[1] = char(hours % 10) + '0';
	time[3] = char(minuts / 10) + '0'; time[4] = char(minuts % 10) + '0';
	time[6] = char(seconds / 10) + '0'; time[7] = char(seconds % 10) + '0';
	time[2] = time[5] = '.';

	return time;

}

struct data_set
{
	int year;
	int month;
	int day;
	int seconds;
	double el;

	data_set() {
		year = 0;
		month = 0;
		day = 0;
		seconds = 0;
		el = 0;
	};

	data_set(string buf) {
		year = get_data_int(buf, 0, 4);
		month = get_data_int(buf, 4, 2);
		day = get_data_int(buf, 6, 2);
		el = find_el(buf);
		seconds = get_time(buf);
	};

	void read(ifstream& in) {
		in.read((char*)&year, sizeof(int));
		in.read((char*)&month, sizeof(int));
		in.read((char*)&day, sizeof(int));
		in.read((char*)&seconds, sizeof(int));
		in.read((char*)&el, sizeof(double));
	};

	void write(ofstream& out) {
		out.write((char*)&year, sizeof(int));
		out.write((char*)&month, sizeof(int));
		out.write((char*)&day, sizeof(int));
		out.write((char*)&seconds, sizeof(int));
		out.write((char*)&el, sizeof(double));
	};

	void print() {
		cout << year << ' ' << month << ' ' << day << ' ' << seconds << ' ' << el << endl;
	}

	bool seted() {
		if (seconds != 0 && el != 0)
			return true;
		else
			return false;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");

	string buf;
	int year_f, month_f, day_f, step = 0;
	bool not_started = true, below = false;
	cout << "Введите дату формата (гггг.мм.дд): ";
	cin >> buf;
	cout << endl;

	string filename = "new_files/new_moon" + buf.substr(0, 4) + ".bin";
	ifstream in(filename, ios::binary);

	year_f = int(buf[0] - '0') * 1000 + int(buf[1] - '0') * 100 + int(buf[2] - '0') * 10 + int(buf[3] - '0');
	month_f = int(buf[5] - '0') * 10 + int(buf[6] - '0');
	day_f = int(buf[8] - '0') * 10 + int(buf[9] - '0');

	data_set values, buf_values, sunrise, sunset;
	cout << month_f << ' ' << day_f << endl;

	buf_values.read(in);
	values.read(in);
	values.print();
	cout << filename << endl;
	step = values.seconds - buf_values.seconds;
	cout << step << ' ' << 86400 / step << ' ' << count_bytes_to_move(year_f, month_f, day_f, step) << endl;
	in.seekg(count_bytes_to_move(year_f, month_f, day_f, step));

	data_set max_el_values;
	int counter = 0;
	int month = 1;

	while (/*!in.eof()*/day_f == values.day || not_started) {
		/*if (month != values.month) {
			values.print();
			cout << counter << endl;
			counter = 0;
			month = values.month;
		}*/
		values.read(in);
		//values.print();
		if (not_started) {
			values.print();
			while (day_f != values.day || month_f != values.month) {
				//values.print();
				values.read(in);
				if (in.eof()) {
					return -1;
				}
			}
			not_started = false;
		}
		//cout << counter << endl;
		if (!sunrise.seted() || !sunset.seted()) {
			if (below && values.el > 0) {
				below = false;
				sunrise = values;
			}
			if (!below && values.el < 0) {
				sunset = values;
				below = true;
			}
		}

		if (values.el > max_el_values.el)
			max_el_values = values;

		counter += 1;
	}

	cout << endl;
	//cout << counter - 1 << ' ';
	cout << "Зенит луны в : " << set_time(max_el_values.seconds) << ", высота луны : " <<  max_el_values.el << endl;
	cout << "Закат луны в : " << set_time(sunset.seconds - step / 2) << ' ' << sunset.el << endl;
	cout << "Восход луны в : " << set_time(sunrise.seconds - step / 2) << ' ' << sunrise.el << endl;

	in.close();
	return 10;
}