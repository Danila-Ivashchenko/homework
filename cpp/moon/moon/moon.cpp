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
                return buf;
            count += 1;
            buf = "";
        }
    }
}

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string date;
    cout << "Input date (fmt: dd.mm.yyyy): ";
    cin >> date;

    double time_s = clock();

    string filename = "../datas/moon" + date.substr(6, 4) + ".dat", dd = date.substr(0, 2), mm = date.substr(3, 2), line;
    cout << filename << endl;

    ifstream file(filename);

    bool down = false;
    double min = 180, buf_el = 0, max_el = 0;
    string  sunrise = "", sunset = "", buf = "", max_height;

    while (getline(file, line).good()) {
        if (mm == line.substr(4, 2) and dd == line.substr(6, 2)) {
            //cout << line << endl;
            double el = find_zero(line);
            if (buf_el && (sunrise == "" || sunset == "")) {
                if (down && el >= 0) {
                    down = false;
                    sunrise = line;
                }
                if (!down && el <= 0) {
                    sunset = line;
                    down = true;
                }
            }
            if (el > max_el) {
                max_el = el;
                max_height = line;
            }
            down = el < 0;
            buf_el = el;
        }
    }

    double time_e = clock();

    cout << endl << "Максимальная высота:\t" << max_height << endl << sunrise << endl << sunset << endl;
    cout << (time_e - time_s) / 1000;

    //cout << endl << min_str << "\n" << min;


    file.close();
    return 0;
}