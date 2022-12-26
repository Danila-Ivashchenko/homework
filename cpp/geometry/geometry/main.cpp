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
    vector <Point> points; points.push_back(a); points.push_back(b); points.push_back(c); points.push_back(d2);
    Polygon pl(points);

    tr1.name();
    tr1.show_points();
    cout << "S = " << tr1.square() << endl;
    cout << "P = " << tr1.perimetr() << endl << endl;

    pl.name();
    pl.show_points();
    cout << "S = " << pl.square() << endl;
    cout << "P = " << pl.perimetr() << endl << endl;

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

bool is_noize(int i, int j, int** arr, int size) {
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

    while (true) {
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

    for (int i = 0; i < h.size() - 1; i++) {
        for (int j = i + 2; j < h.size() - 1; j++) {
            double rot = rotate(arr_points[h[i]], arr_points[h[j]], arr_points[h[j - 1]]);
            if (rot == 0) {
                h.erase(h.begin() + j - 1);
                j--;
            }
        }
    }

    vector <Point> new_points;
    for (auto index : h)
        new_points.push_back(arr_points[index]);
    Polygon polygon(new_points);

    int h_right = 0;
    int h_left = 0;

    for (int i = 0; i < h.size(); i++) {
        if (arr_points[h[i]].x > arr_points[h[h_left]].x)
            h_left = i;
        if (arr_points[h[i]].x < arr_points[h[h_right]].x)
            h_right = i;
    }

    int h_last = 0;
    int rotate_last = 0;

    for (int i = 0; i < h.size(); i++) {
        if (abs(rotate(arr_points[h[h_right]], arr_points[h[h_left]], arr_points[h[i]])) > rotate_last) {
            rotate_last = abs(rotate(arr_points[h[h_right]], arr_points[h[h_left]], arr_points[h[i]]));
            h_last = i;
        }
    }

    cout << arr_points[h[h_right]] << ", " << arr_points[h[h_left]] << ", " << arr_points[h[h_last]] << ", points - " << arr_points.size() << ", squer - " << polygon.square() << endl;
    
    bool is_noize = arr_points.size() < polygon.square();
    cout << is_noize << endl;
    return arr_points.size() < polygon.square();

    //int i_hight = int(max(max(arr_points[h[h_right]].y, arr_points[h[h_left]].y), arr_points[h[h_last]].y));
    //int i_low = int(min(min(arr_points[h[h_right]].y, arr_points[h[h_left]].y), arr_points[h[h_last]].y));

    //cout << "i_hight - " << i_hight << ", i_low - " << i_low << ", " << i_hight - i_low << endl;

    //int j_left = j;
    //int j_right = 0;
    //for (int c = j; arr[i_low][c] == 1; c++)
    //    j_right = c;


    //bool is_noize = false;
    //cout << "right - " << j_right << " left - " << j_left << endl;

    //for (int v = i_low; i < i_hight && !is_noize; v++) {
    //    //cout << "i = " << v << endl;
    //    for (int c = j_left; c < j_right; c++) {
    //        if (arr[v][c] != 1) {
    //            cout << "NOIZE " << v << " ; " << c << endl;
    //            is_noize = true;
    //            break;
    //        }
    //    }
    //    if (arr[v + 1][j_right + 1] == 1)
    //        j_right += 1;
    //    else if (arr[v + 1][j_right] == 1)
    //        j_right += 0;
    //    else if (arr[v + 1][j_right - 1] == 1)
    //        j_right -= 1;
    //    else
    //        j_right = -1;

    //    if (arr[v + 1][j_left - 1] == 1)
    //        j_left -= 1;
    //    else if (arr[v + 1][j_left] == 1)
    //        j_left += 0;
    //    else if (arr[v + 1][j_left + 1] == 1)
    //        j_left += 1;
    //    else
    //        j_left = -1;
    //    //cout << "right - " << j_right << " left - " << j_left << endl;

    //    if (j_left < 0 || j_right < 0) {
    //        cout << "j_right - " << j_right << " j_left - " << j_left << " i - " << v << endl;
    //        if (v != i_hight)
    //            is_noize = true;
    //        break;
    //    }
    //    if (j_left > j_right) {
    //        cout << "j_right - " << j_right << " j_left - " << j_left << " i - " << v << endl;
    //        if (v != i_hight)
    //            is_noize = true;
    //        break;
    //    }
    //}

}

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

    for (int i = 0; i < h.size() - 1; i++) {
        for (int j = i + 2; j < h.size() - 1; j++) {
            double rot = rotate(arr_points[h[i]], arr_points[h[j]], arr_points[h[j - 1]]);
            if ( rot == 0) {
                h.erase(h.begin() + j - 1);
                j--;
            }
        }
    }
    int h_right = 0;
    int h_left = 0;
    
    for (int i = 0; i < h.size(); i++) {
        if (arr_points[h[i]].x > arr_points[h[h_left]].x)
            h_left = i;
        if (arr_points[h[i]].x < arr_points[h[h_right]].x)
            h_right = i;
    }

    int h_last = 0;
    int rotate_last = 0;

    for (int i = 0; i < h.size(); i++) {
        if (abs(rotate(arr_points[h[h_right]], arr_points[h[h_left]], arr_points[h[i]])) > rotate_last) {
            rotate_last = abs(rotate(arr_points[h[h_right]], arr_points[h[h_left]], arr_points[h[i]]));
            h_last = i;
        }
    }

    cout << arr_points[h[h_right]] << ", " << arr_points[h[h_left]] << ", " << arr_points[h[h_last]] << ", points - " << arr_points.size() << endl;
    //cout << arr_points[h[h_right]].vector_distance(arr_points[h[h_left]]) << ", " << arr_points[h[h_left]].vector_distance(arr_points[h[h_last]]) << ", " << arr_points[h[h_last]].vector_distance(arr_points[h[h_right]]) << ", points - " << arr_points.size() << endl;

    int i_hight = int(max(max(arr_points[h[h_right]].y, arr_points[h[h_left]].y), arr_points[h[h_last]].y));
    int i_low = int(min(min(arr_points[h[h_right]].y, arr_points[h[h_left]].y), arr_points[h[h_last]].y));

    cout << i_hight << ", " << i_low << ", " << i_hight - i_low << endl;

    int j_left = j;
    int j_right = 0;
    for (int c = j; arr[i_low][c] == 1; c++)
        j_right = c;
    

    bool is_noize = false;
    cout << "left - " << j_left << ", right - " << j_right << endl;
    for (int v = i_low; i < i_hight; i++) {
        for (int c = j_left; c < j_right; c++) {
            if (arr[v][c] != 1) {
                cout << v << " ; " << c << endl;
                is_noize = true;
                break;
            }
        }
        if (arr[v + 1][j_right - 1] == 1)
            j_right -= 1;
        else if (arr[v + 1][j_right] == 1)
            j_right += 0;
        else if (arr[v + 1][j_right + 1] == 1)
            j_right += 1;
        else
            j_right = -1;

        if (arr[v + 1][j_left + 1] == 1)
            j_left += 1;
        else if (arr[v + 1][j_left] == 1)
            j_left += 0;
        else if (arr[v + 1][j_left - 1] == 1)
            j_left -= 1;
        else
            j_left = -1;

        if (j_left < 0 || j_right < 0) {
            is_noize = true;
            cout << "left - " << j_left << ", right - " << j_right << endl;
            break;
        }
    }

    cout << "is noize - " << is_noize << endl;

    //for (int i = 0; i < h.size() - 1; i++) {
    //    cout << arr_points[h[i]] << endl;
    //    for (int j = i + 2; j < h.size() - 1; j++)
    //        cout << "\t" << arr_points[h[j - 1]] << ", " << arr_points[h[j]] << " - " << rotate(arr_points[h[i]], arr_points[h[j - 1]], arr_points[h[j]]) << endl;
    //}

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
    //print_tests();

    //ifstream file("files/noize.txt");
    //int size = 30;

    ifstream file("files/input1.dat");
    int size = 200;

    //ifstream file("files/elips.txt");

    
    int** points = new int*[size];
    set <int*> banned_points;
    vector <Rectangle> rectangls;
    int rectangles_count = 0;
    vector <Elips> elipses;
    int elipses_count = 0;
    vector <Triangle> triangles;
    int triangles_count = 0;
    vector <Figure*> figures;

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
                    cout << "Is elips" << endl << endl;
                    ban_points(i, j, points, size, banned_points);
                    elipses.push_back(make_elips(i, j, points, size));
                    //cout << &elipses[elipses_count] << endl;
                    //figures.push_back(&elipses[elipses_count]);
                    elipses_count += 1;
                } else if (is_rectangle(i, j, points, size)) {
                    cout << "Is rectangle" << endl << endl;
                    ban_points(i, j, points, size, banned_points);
                    rectangls.push_back(make_rectangle(i, j, points, size));
                    //cout << &rectangls[rectangles_count] << endl;
                    //figures.push_back(&rectangls[rectangles_count]);
                    rectangles_count += 1;
                }
                /*else if (mos(i, j, points, size).size()){
                    cout << "Is triangle" << endl;
                    cout << "j - " << j << ", i - " << i << endl;
                    ban_points(i, j, points, size, banned_points);
                }*/
                else if (is_noize(i, j, points, size)) {
                    ban_points(i, j, points, size, banned_points);
                    cout << "Is noize" << endl;
                    cout << "i - " << i << " j - " << j << endl;
                    //cout << p.size() << endl;
                    //for (int i = 0; i < p.size(); i++)
                    //    cout << i << " - " << p[i] << endl;
                    //cout << "j - " << j << ", i - " << i << endl;
                }
                else {
                    ban_points(i, j, points, size, banned_points);
                    cout << "Is triangle" << endl;
                    cout << "i - " << i << " j - " << j << endl;
                }
            }
        }
    }

    //for (int i = 0; i < rectangls.size(); i++)
    //    figures.push_back(&rectangls[i]);
    //for (int i = 0; i < elipses.size(); i++)
    //    figures.push_back(&elipses[i]);

    //cout << endl;
    //int sum = 0;
    //for (auto f : figures) {
    //    sum += f->square();
    //    cout << f << endl;
    //}


    ////cout << endl;

    ////for (int i = 0; i < elipses.size(); i++) {
    ////    cout <<  &elipses[i] << endl;
    ////    (&elipses[i])->name();
    ////    (&elipses[i])->show_points();
    ////}
    //
    //cout << endl << sum;

    return 10;
}
