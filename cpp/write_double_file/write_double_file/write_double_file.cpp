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

int get_count_of_month(int month) {
	switch (month)
	{
	case 1:
		return 31;
		break;
	case 2:
		return 28;
		break;
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
	case 12:
		return 31;
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


int count_bytes_to_move(int month, int day, int step) {
	int day_in_months = 0;
	month -= 1;
	day -= 1;
	if (month > 0)
		while (month > 0) {
			day_in_months += get_count_of_month(month);
			month -= 1;
		}
	return (day + day_in_months) * (4 * sizeof(int) + sizeof(double)) * (86400 / step);
}

int get_time(string str) {
	int hours = get_data_int(str, 8, 2);
	int minuts = get_data_int(str, 11, 2);
	return get_data_int(str, 13, 2) + minuts * 60 + hours * 60 * 60;
}

char *set_time(int seconds) {
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
	char space_buf;
	cin >> buf;
	while (buf != "") {
		string filename = "old_files/moon", new_filename = "new_files/new_moon";
		filename += buf + ".dat";
		new_filename += buf + ".bin";

		ifstream in(filename);
		getline(in, buf);
		ofstream out(new_filename, ios::binary);

		while (getline(in, buf).good()) {
			data_set data(buf);
			data.print();
			data.write(out);
		}

		cout << new_filename << " сохранён" << endl;
		out.close();
		cin >> buf;
	}
	return 1;
}