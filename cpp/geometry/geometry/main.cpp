#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <math.h>
#include "Figures.h"

using namespace std;

// расстояние от точки c до вектора a -> b 
double rotate(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

// запрет точек для проверки (точки входят в состав добавленной фигуры)
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

// заполнение вектора точками, стоящими рядом
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

// поиск рядом стоящих точек, равных 1
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
    double r1 = 0, r2 = 0;
    int i_center = i, j_center = j;

    for (int c = i; c < size && arr[c][j] == 1; c++) {
        int buf_rad1 = 0;
        for (int j1 = j; j1 > 0 && arr[c][j1] == 1; j1--) {
            if (arr[c][j1] == 1)
                buf_rad1++;
        }
        if (buf_rad1 > r1) {
            i_center = c;
            r1 = buf_rad1;
        }
        else
            break;
        r2++;
    }

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

// поиск минимальный выпуклой оболочки, возвращает вектор точек
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

bool is_noize(int i, int j, int** arr, int size) {
    vector <Point> all_points = find_points(i, j, arr, size);

    vector <Point> mos_points = mos(i, j, arr, size);
    Polygon polygon(mos_points);

    bool is_noize = all_points.size() < polygon.square();
    // суть провекри в том, что если площадь МВО больше фактической площади фигуры (количества едениц, в пределах 1 фигуры), то значит, что фигура невыпуклая - шум 
    return all_points.size() < polygon.square() || mos_points.size() < 3;
}

int noize_square(int i, int j, int** arr, int size) {
    return find_points(i, j, arr, size).size();
}

// треугольник
Triangle make_triangle_2(int i, int j, int** arr, int size) {

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

    return Triangle(arr_points[h[h_right]], arr_points[h[h_left]], arr_points[h[h_last]]);
}

Triangle make_triangle(int i, int j, int** arr, int size) {
    vector <Point> arr_points = mos(i, j, arr, size);

    int h_right = 0;
    int h_left = 0;

    for (int i = 0; i < arr_points.size(); i++) {
        if (arr_points[i].x > arr_points[h_left].x)
            h_left = i;
        if (arr_points[i].x < arr_points[h_right].x)
            h_right = i;
    }

    int h_last = 0;
    int rotate_last = 0;

    for (int i = 0; i < arr_points.size(); i++) {
        if (abs(rotate(arr_points[h_right], arr_points[h_left], arr_points[i])) > rotate_last) {
            rotate_last = abs(rotate(arr_points[h_right], arr_points[h_left], arr_points[i]));
            h_last = i;
        }
    }

    return Triangle(arr_points[h_right], arr_points[h_left], arr_points[h_last]);
}

int main()
{
    ifstream file("files/input1.dat");
    int size = 200;
    
    int** points = new int*[size]; // двумерный массив точек (0, 1) из файла

    set <int*> banned_points; // сет указателей на точки, которые находятся в фигурах, которые уже нашли

    vector <Rectangle> rectangles; // массив прямоугольников
    int rectangles_count = 0;

    vector <Elips> elipses; // массив элипсов
    int elipses_count = 0;

    vector <Triangle> triangles; // массив триугольников
    int triangles_count = 0;

    vector <Polygon> noizes; // массив шумов
    int noizes_count = 0;

    vector <Figure*> figures; // массив указателей на все фигуры

    int noize_squares = 0; // суммарная площадь шумов
    double rectangle_squares = 0; // суммарная площадь прямоугольников
    double elips_squares = 0; // суммарная площадь элипсов
    double triangle_squares = 0; // суммарная площадь треугольников

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
                    //cout << "Is elips" << endl << endl;
                    ban_points(i, j, points, size, banned_points);
                    elipses.push_back(make_elips(i, j, points, size));
                    elips_squares += elipses[elipses_count].square();
                    elipses_count += 1;
                } else if (is_rectangle(i, j, points, size)) {
                    //cout << "Is rectangle" << endl << endl;
                    ban_points(i, j, points, size, banned_points);
                    rectangles.push_back(make_rectangle(i, j, points, size));
                    rectangle_squares += rectangles[rectangles_count].square();
                    rectangles_count += 1;
                }
                else if (is_noize(i, j, points, size)) {
                    ban_points(i, j, points, size, banned_points);
                    //cout << "Is noize" << endl;
                    noizes.push_back(mos(i, j, points, size));
                    noize_squares += noize_square(i, j, points, size);
                    noizes_count += 1;
                }
                else {
                    ban_points(i, j, points, size, banned_points);
                    //cout << "Is triangle" << endl;
                    triangles.push_back(make_triangle(i, j, points, size));
                    triangle_squares += triangles[triangles_count].square();
                    triangles_count += 1;
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
        delete points[i];
    delete points;

    for (int i = 0; i < rectangles.size(); i++)
        figures.push_back(&rectangles[i]);
    for (int i = 0; i < elipses.size(); i++)
        figures.push_back(&elipses[i]);
    for (int i = 0; i < triangles.size(); i++)
        figures.push_back(&triangles[i]);

    cout << "Triangles:" << endl;
    cout << "\tcount - " << triangles_count << ", total area = " << triangle_squares << endl;
    cout << "Elipses:" << endl;
    cout << "\tcount - " << elipses_count << ", total area = " << elips_squares << endl;
    cout << "Rectangles:" << endl;
    cout << "\tcount - " << rectangles_count << ", total area = " << rectangle_squares << endl;
    cout << "Noizes:" << endl;
    cout << "\tcount - " << noizes_count << ", total area = " << noize_squares << endl;

    return 1;
}
