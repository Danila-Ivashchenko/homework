#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

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

double find_zero(string str) {
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

string fix_time(string& time, double& d) {
    int all_time = 0, step = 36000;
    for (int i = 0; i < 8; i++) {
        if (time[i] != '.') {
            all_time += step * int(time[i] - '0');
            step /= 10;
        }
        else {
            step /= 60;
        }
    }
    all_time -= int(d);
    int hours = all_time / 3600;
    all_time %= 3600;
    int minuts = all_time / 60;
    all_time %= 60;
    int seconds = all_time;
    time[0] = char(hours / 10 + '0'), time[1] = char(hours % 10 + '0');
    time[3] = char(minuts / 10 + '0'), time[4] = char(minuts % 10 + '0');
    time[6] = char(seconds / 10 + '0'), time[7] = char(seconds % 10 + '0');
    return time;
}

string find_time(string str) {
    string buf;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ' && str[i] != '\t')
            buf += str[i];
        else {
            if (buf == "")
                continue;
            if (count == 1)
                return buf.substr(0, 2) + '.' + buf.substr(2, 2) + '.' + buf.substr(4, 2);
            count += 1;
            buf = "";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    string date;
    cout << "Input date (fmt: dd.mm.yyyy): ";
    cin >> date;

    double time_s = clock();

    string filename = "moon" + date.substr(6, 4) + ".dat", dd = date.substr(0, 2), mm = date.substr(3, 2), line;
    cout << filename << endl;

    ifstream file(filename);

    bool down = false, flag = false;
    double min = 180, buf_el = 0, max_el_f = 0, max_el_m = 0, max_el_l = 0;
    string  sunrise = "", sunset = "", buf = "", max_height_f = "", max_height_m = "", max_height_l = "";

    while (getline(file, line).good()) {
        if (mm == line.substr(4, 2) and dd == line.substr(6, 2)) {
            //cout << line << endl;
            double el = find_zero(line);
            string time = find_time(line);
            if (buf_el && (sunrise == "" || sunset == "")) {
                if (down && el >= 0) {
                    down = false;
                    sunrise = time;
                }
                if (!down && el <= 0) {
                    sunset = time;
                    down = true;
                }
            }
            if (el > max_el_f || flag) {
                max_el_l = max_el_m;
                max_el_m = max_el_f;
                max_el_f = el;
                max_height_l = max_height_m;
                max_height_m = max_height_f;
                max_height_f = time;
                if (el > max_el_m)
                    flag = true;
                else
                    flag = false;
            }
            down = el < 0;
            buf_el = el;
        }
    }

    double time_e = clock();
    double befor = max_el_m - max_el_l, after = max_el_m - max_el_f, d = after - befor;
    double step = stoi(max_height_f.substr(3, 2)) - stoi(max_height_m.substr(3, 2)), d_time = step * d * 60;
    if (d_time > 0)
        d_time /= after;
    else
        d_time /= befor;

    cout << "Время работы программы: " << (time_e - time_s) / 1000;
    cout << endl << "Максимальная высота в:\t" << fix_time(max_height_m, d_time) << endl << "Восход луны в: " << sunrise << endl << "Закат луны в: " << sunset << endl;



    file.close();
    return 0;
}