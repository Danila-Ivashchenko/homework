#include <iostream>
#include <chrono>
#include "class_array.h"

using namespace std;

Array setArray(const int& n) {
    Array arr(n);
    for (int i = 0; i < n; i++)
        arr.insert(i + 1);
    return arr;
}

void iosif(const int& k,const int& n, Array& arr) {
    double start = clock();
    int pos = (k - 1) % n;
    while (arr.getSize() != 1) {
        //cout << arr[pos] << endl;
        arr.remove(pos);
        pos = (pos + k - 1) % arr.getSize();
        //cout << "array - " << arr << endl;
        //cout << pos << endl;
    }
    double end = clock();
    cout << "n = " << n << ", time = " << (end - start) / 1000 << endl;
    cout << arr << endl;
}

int iosif_by_id(int k, int n) {
    int p = 1;
    while (p <= n)
        p *= 2;
    return (2 * n) - p + 1;
}

void full_iosif(const int& k, int n) {
    Array arr = setArray(n);
    iosif(k, n, arr);
}

int main()
{
    int n = 1000, k = 2;
    for (int i = 0; i < 7; i++) {
        if (i > 0) {
            if (i % 2 == 0)
                n *= 2;
            else
                n *= 5;
        }
        full_iosif(k, n);
        double start = clock();
        cout << "n = " << n << ", answer = " << iosif_by_id(k, n) << ", time = " << (clock() - start) / 1000 << endl;
    }

    return 10;
}