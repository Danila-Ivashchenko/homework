#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <math.h>
#include "Figures.h"

using namespace std;

void print_tests() {
    Point a(-1, -3), b(3, 4), c(5, -5);
    Point a1(1, 1), b1(1, 4), c1(5, 4), d1(5, 1);
    Point c2(4, 4), d2(4, 1);
    Triangle tr1(a, b, c);
    Rectangle rt1(a1, b1, c1, d1);
    Square sq1(a1, b1, c2, d2);
    Elips el1(2, 4, Point(5, 5));
    Circle cl1(4.12, Point(5, 5));

    tr1.name();
    tr1.show_points();
    cout << "S = " << tr1.square() << endl;
    cout << "P = " << tr1.perimetr() << endl << endl;

    rt1.name();
    rt1.show_points();
    cout << "S = " << rt1.square() << endl;
    cout << "P = " << rt1.perimetr() << endl << endl;


    sq1.name();
    sq1.show_points();
    cout << "S = " << sq1.square() << endl;
    cout << "P = " << sq1.perimetr() << endl << endl;

    el1.name();
    el1.show_points();
    cout << "S = " << el1.square() << endl;
    cout << "P = " << el1.perimetr() << endl << endl;

    cl1.name();
    cl1.show_points();
    cout << "S = " << cl1.square() << endl;
    cout << "P = " << cl1.perimetr() << endl << endl;

    cout << tr1.square() << " " << rt1.square() << " " << sq1.square();
}


double rotate(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

void ban_points(int i, int j, int** arr, int size, set <int*> &banned) {
    if (arr[i][j] == 1 && banned.find(&arr[i][j]) == banned.end()) {
        banned.insert(&arr[i][j]);
        if (i - 1 >= 0) {
            if (j - 1 >= 0)
                ban_points(i - 1, j - 1, arr, size, banned);
            if (j + 1 < size)
                ban_points(i - 1, j + 1, arr, size, banned);
            ban_points(i - 1, j, arr, size, banned);
        }
        if (i + 1 < size) {
            if (j - 1 >= 0)
                ban_points(i + 1, j - 1, arr, size, banned);
            if (j + 1 < size)
                ban_points(i + 1, j + 1, arr, size, banned);
            ban_points(i + 1, j, arr, size, banned);
        }
        if (j - 1 >= 0)
            ban_points(i, j - 1, arr, size, banned);
        if (j + 1 < size)
            ban_points(i, j + 1, arr, size, banned);
    }
}
bool point_in_vector(const Point& p, vector <Point>& arr) {
    for (auto point : arr){
        if (point == p)
            return true;
    }
    return false;
}

void fill_points(int i, int j, int** arr, int size, vector <Point>& arr_points) {
    if (arr[i][j] == 1) {
        Point point(j, i);
        if (!point_in_vector(point, arr_points)) {
            arr_points.push_back(point);
            if (i - 1 >= 0) {
                if (j - 1 >= 0)
                    fill_points(i - 1, j - 1, arr, size, arr_points);
                if (j + 1 < size)
                    fill_points(i - 1, j + 1, arr, size, arr_points);
                fill_points(i - 1, j, arr, size, arr_points);
            }
            if (i + 1 < size) {
                if (j - 1 >= 0)
                    fill_points(i + 1, j - 1, arr, size, arr_points);
                if (j + 1 < size)
                    fill_points(i + 1, j + 1, arr, size, arr_points);
                fill_points(i + 1, j, arr, size, arr_points);
            }
            if (j - 1 >= 0)
                fill_points(i, j - 1, arr, size, arr_points);
            if (j + 1 < size)
                fill_points(i, j + 1, arr, size, arr_points);
        }
    }
}

vector <Point> find_points(int i, int j, int** arr, int size) {
    vector <Point> arr_points;
    fill_points(i, j, arr, size, arr_points);
    return arr_points;
}

// элипс

bool is_elips(int i, int j, int** arr, int size) {
    bool is_elips = false;
    int r1 = 0, r2 = 0;
    int i_center = i, j_center = j;
    bool up = true;

    if (i + 1 >= size || j + 1 >= size || j == 0)
        return false;
    int buf_rad1 = 0, buf_rad2 = 0;
    for (int c = i + 1; c < size && arr[c][j] == 1; c++) {
        int buf_rad1_last = buf_rad1, buf_rad2_last = buf_rad2;
        buf_rad1 = 0; buf_rad2 = 0;
        for (int j1 = j - 1; j1 > 0 && arr[c][j1] == 1; j1--) {
            if (arr[c][j1] == 1)
                buf_rad1 += 1;
        }
        for (int j2 = j + 1; j2 > 0 && arr[c][j2] == 1; j2++) {
            if (arr[c][j2] == 1)
                buf_rad2 += 1;
        }
        //cout << buf_rad1 << " " << buf_rad2 << endl;
        if (buf_rad1 == buf_rad2 && buf_rad1 != 1 && buf_rad1 != 0) {
            is_elips = true;
        }
        if (buf_rad1_last < buf_rad1 && !up)
            return false;
        if (buf_rad1_last > buf_rad1 && up)
            up = false;
    }
    return is_elips && !up;
}

Elips make_elips(int i, int j, int** arr, int size) {
    bool r1 = 0, r2 = 0;
    int i_center = i, j_center = j;

    for (int c = i + 1; c < size && arr[c][j] == 1; c++) {
        int buf_rad1 = 0;
        for (int j1 = j - 1; j1 > 0 && arr[c][j1] == 1; j1--) {
            if (arr[c][j1] == 1)
                buf_rad1 += 1;
        }
        if (buf_rad1 > r1) {
            i_center = c;
            r1 = buf_rad1;
        }
        r2 += 1;
    }
    r1 += 0.5;
    r2 /= 2;
    Point center(j_center, i_center);
    return Elips(r1, r2, center);
}

// прямоугольник

bool is_rectangle(int i, int j, int** arr, int size) {
    bool is_rectangle = true;
    int i_low = i;
    int i_hig = i;
    int j_low = j;
    int j_hig = j;
    
    for (int c = i; c < size && arr[c][j] != 0; c++)
        i_low = c;
    for (int c = j; c < size && arr[i][c] != 0; c++)
        j_hig = c;

    if (i_low == i_hig)
        return false;

    if (j_low == j_hig)
        return false;

    for (int c = i_hig; c <= i_low; c++) {
        for (int v = j_low; v <= j_hig; v++) {
            if (arr[c][v] != 1)
                return false;
        }
    }

  /*  Point a(j_low, i_low), b(j_low, i_hig), c(j_hig, i_hig), d(j_hig, i_low);
    cout << b << ", " << c << endl;
    cout << a << ", " << d << endl;
    cout << j_low << " - " << j_hig << endl;
    cout << i_low << " - " << i_hig << endl;*/
    
    return is_rectangle;
}

Rectangle make_rectangle(int i, int j, int** arr, int size) {
    int i_low = i;
    int i_hig = i;
    int j_low = j;
    int j_hig = j;

    for (int c = i; c < size && arr[c][j] != 0; c++)
        i_low = c;
    for (int c = j; c < size && arr[i][c] != 0; c++)
        j_hig = c;

    Point a(j_low, i_low), b(j_low, i_hig), c(j_hig, i_hig), d(j_hig, i_low);
    return Rectangle(a, b, c, d);
}

// шум

vector <Point>  mos(int i, int j, int** arr, int size) {
    vector <Point> arr_points = find_points(i, j, arr, size);
    
    int n = arr_points.size();
    vector <int> p;

    for (int i = 0; i < n; i++)
        p.push_back(i);

    for (int i = 0; i < n; i++)
        if (arr_points[i].x < arr_points[0].x)
            swap(arr_points[i], arr_points[0]);

    vector <int> h;
    h.push_back(p[0]);
    p.erase(p.begin());
    p.push_back(h[0]);

    while (true){
        int right = 0;
        for (int i = 1; i < p.size(); i++)
            if (rotate(arr_points[h[h.size() - 1]], arr_points[p[right]], arr_points[p[i]]) < 0)
                right = i;
        if (p[right] == h[0])
            break;
        else {
            h.push_back(p[right]);
            p.erase(p.begin() + right);
        }
    }

    //for (auto index : h)
    //    cout << "h - " << arr_points[index] << endl;
    //cout << endl;


    //for (int i = 0; i < h.size() - 1; i++) {
    //    for (int j = i + 2; j < h.size() - 1; j++) {
    //        for (int c = i + 1; c < j; c++) {
    //            if (rotate(arr_points[h[i]], arr_points[h[j]], arr_points[h[c]]) == 0) {
    //                h.erase(h.begin() + c);
    //                c--;
    //            }
    //        }
    //    }
    //}

    for (int i = 0; i < h.size() - 1; i++) {
        for (int j = i + 2; j < h.size() - 1; j++) {
            if (rotate(arr_points[h[i]], arr_points[h[j]], arr_points[h[j - 1]]) == 0) {
                h.erase(h.begin() + j - 1);
                j--;
            }
        }
    }


    for (int i = 0; i < h.size() - 1; i++) {
        cout << arr_points[h[i]] << endl;
        for (int j = i + 2; j < h.size() - 1; j++)
            cout << "\t" << arr_points[h[j - 1]] << ", " << arr_points[h[j]] << " - " << rotate(arr_points[h[i]], arr_points[h[j - 1]], arr_points[h[j]]) << endl;
    }

    if (h.size() > 2) {
        if (rotate(arr_points[h[0]], arr_points[h[h.size() - 1]], arr_points[h[h.size() - 2]]) == 0)
            h.erase(h.begin() + h.size() - 1);
    }

    for (int i = 0; i < h.size() - 1; i++) {
        if (arr_points[h[i]].vector_distance(arr_points[h[i + 1]]) == 1)
            h.erase(h.begin() + i);
    }
    if (arr_points[h[0]].vector_distance(arr_points[h[h.size() - 1]]) == 1)
        h.erase(h.begin() + h.size() - 1);
    
    vector <Point> new_points;
    for (auto index : h)
        new_points.push_back(arr_points[index]);

    return new_points;
}

int main()
{
    //ifstream file("files/input1.dat");
    ifstream file("files/noize.txt");
    //ifstream file("files/elips.txt");
    //int size = 200;
    int size = 30;
    int** points = new int*[size];
    set <int*> banned_points;

    for (int i = 0; i < size; i++) {
        points[i] = new int[size];
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char buf;
            file >> buf;
            points[i][j] = int(buf - '0');
            //cout << points[i][j];
        }
        //cout << endl;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (points[i][j] == 1 && banned_points.find(&points[i][j]) == banned_points.end()) {
                if (is_elips(i, j, points, size)) {
                    cout << "Is elips" << endl;
                    ban_points(i, j, points, size, banned_points);
                    //make_elips(i, j, points, size).show_points();
                } else if (is_rectangle(i, j, points, size)) {
                    cout << "Is rectangle" << endl;
                    ban_points(i, j, points, size, banned_points);
                    //make_rectangle(i, j, points, size).show_points();
                }
                /*else if (mos(i, j, points, size).size()){
                    cout << "Is triangle" << endl;
                    cout << "j - " << j << ", i - " << i << endl;
                    ban_points(i, j, points, size, banned_points);
                }*/
                else {
                    ban_points(i, j, points, size, banned_points);
                    vector <Point> p = mos(i, j, points, size);
                    cout << p.size() << endl;
                    for (int i = 0; i < p.size(); i++)
                        cout << i << " - " << p[i] << endl;
                    cout << "j - " << j << ", i - " << i << endl;

                }
            }
        }
    }

    
    return 10;
}
