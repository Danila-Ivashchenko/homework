#include <iostream>
#include <fstream>
#include "Figures.h"
#include <vector>
#include <set>

using namespace std;

// блокировка точек, для исключения добовления подфигур
void ban_points(int i, int j, int** arr, int size, set <int*> &banned_points) {

    if (arr[i][j] == 1 && banned_points.find(&arr[i][j]) == banned_points.end()) {
        banned_points.insert(&arr[i][j]);
        if (i + 1 < size) {
            ban_points(i + 1, j, arr, size, banned_points);
            if (j + 1 < size)
                ban_points(i + 1, j + 1, arr, size, banned_points);
            if (j - 1 >= 0)
                ban_points(i + 1, j - 1, arr, size, banned_points);
        }
        if (i - 1 >= 0) {
            ban_points(i - 1, j, arr, size, banned_points);
            if (j + 1 < size)
                ban_points(i - 1, j + 1, arr, size, banned_points);
            if (j - 1 >= 0)
                ban_points(i - 1, j - 1, arr, size, banned_points);
        }
        if (j + 1 < size)
            ban_points(i, j + 1, arr, size, banned_points);
        if (j - 1 >= 0)
            ban_points(i, j - 1, arr, size, banned_points);
    }
}

bool is_triangle(int i, int j, int** arr, int size) {
    bool is_triangle = false;
    int point_hight_i = i;
    int point_hight_j = j;

    int point_left_i = i;
    int point_left_j = j;

    int point_right_i = i;
    int point_right_j = j;

    int count = 0;
    int last_count = 0;
    bool is_not_zero = true;

    int left_border = j;
    while (is_not_zero && i < size) {
        last_count = count;
        count = 0;
        for (int c = left_border; c < size && arr[i][c] != 0 /*c < right_border*/; c++) {
            //cout << c << " " << arr[i][c] << endl;
            if (arr[i][c] == 1) {
                count += 1;
                cout << arr[i][c];
                if (c <= point_left_j) {
                    point_left_j = c;
                    point_left_i = i;
                }
                else if (c >= point_right_j) {
                    point_right_j = c;
                    point_right_i = i;
                }
            }
        }
        cout << endl;
        if (count == 0) {
            is_not_zero = false;
            break;
        }
        if (last_count != count && count != 1 && count != 0) {
            is_triangle = true;
        }
        i += 1;
        if (arr[i][left_border - 1] == 1)
            left_border--;
        else if (arr[i][left_border] == 1)
            left_border;
        if (arr[i][left_border + 1] == 1)
            left_border++;
        else {
            cout << "i " << i << " left_border " << left_border << endl;
            break;
        }
        
    }
    cout << point_hight_i << " " << point_hight_j << ", " << point_left_i << " " << point_left_j << ", " << point_right_i << " " << point_right_j << endl;
    return is_triangle;
}

bool is_elips(int i, int j, int** arr, int size) {
    bool is_elips = false;
    int j_center = j;
    int i_center = i;
    int j_sum = 0;
    int j_num = 0;

    // поиск центра по оси ox
    //for (int c = j; c < size && arr[i][c] != 0; c++) {
    //    j_sum += c;
    //    j_num += 1;
    //}
    //j_center = j_sum / j_num;

    //cout << "j_center - " << j_center << endl;
    //cout << arr[i+ 1][j_center] << endl;

    //проверка радиусов
    while (i + 1 < size && arr[i][j_center] != 0){
        i += 1;
        if (arr[i][j_center] != 1)
            break;
        int r1 = 0, r2 = 0;
        for (int c1 = j_center + 1; c1 < size && arr[i][c1] != 0; c1++) {
            r1 += 1;
        }
        for (int c2 = j_center - 1; c2 >= 0 && arr[i][c2] != 0; c2--) {
            r2 += 1;
        }
        //cout << r1 << " " << r2 << endl;
        if (r1 != r2) {
            is_elips = false;
            break;
        }
        else {
            is_elips = true;
        }
    }
    return is_elips;
}

Elips find_elips(int i, int j, int** arr, int size){
    int j_center = j;
    int i_center = i;
    int j_sum = 0;
    int j_num = 0;
    double radius_1 = 1;
    double radius_2 = 1;

    // поиск центра по оси ox
    for (int c = j; c < size && arr[i][c] != 0; c++) {
        j_sum += c;
        j_num += 1;
    }
    j_center = j_sum / j_num;

    //поиск радиусов
    while (i + 1 < size && arr[i][j_center] != 0) {
        i += 1;
        int r = 0;
        for (int c = j_center + 1; c < size && arr[i][c] != 0; c++) {
            r += 1;
        }
        if (r > radius_2) {
            radius_2 = r;
            i_center = i;
        }
        radius_1 += 1;
    }
    radius_1 /= 2;
    radius_2 += 0.5;
    //cout << radius_1 << " " << radius_2 << endl;
    //cout << j_center << " " << i_center << endl;
    Point center(j_center, i_center);
    return Elips(radius_1, radius_2, center);
}


bool is_rectangle(int i, int j, int** arr, int size) {
    //cout << "i - " << i << ", j - " << j << endl;
    bool is_rect = true;
    int y_low = -1;
    int y_hig = i;
    int x_low = j;
    int x_hig = -1;

    // поиск крайних точек
    while (i < size) {
        if (arr[i][j] == 0) {
            break;
        }

        else {
            y_low = i;
            i += 1;
        }
    }

    while (j < size) {
        if (arr[y_hig][j] == 0) {
            break;
        }
        else {
            x_hig = j;
            j += 1;
        }
    }

    // проверка, что фигура не линия
    if (y_low == y_hig || x_low == x_hig)
        return false;

    // проверка, что внутри фигуры нет пустот
    for (int i = y_hig; i <= y_low; i++) {
        for (int j = x_low; j <= x_hig; j++) {
            if (arr[i][j] != 1) {
                cout << i << " " << j << endl;
                is_rect = false;
            }
        }
    }

    //cout << y_low << " " << y_hig << " " << x_low << " " << x_hig << endl;
    return is_rect;
}

Rectangle find_rect(int i, int j, int** arr, int size) {
    cout << "i - " << i << ", j - " << j << endl;
    int y_low = i;
    int y_hig = i;
    int x_low = j;
    int x_hig = j;

    // поиск крайних точек
    while (i  < size) {
        if (arr[i][j] == 0) {
            break;
        }
        else {
            y_low = i;
            i += 1;
        }
    }

    while (j < size) {
        if (arr[y_hig][j] == 0) {
            break;
        }
        else {
            x_hig = j;
            j += 1;
        }
    }

    // формирование точек
    Point a(x_low, y_low), b(x_low, y_hig), c(x_hig, y_hig), d(x_hig, y_low);
    //cout << b << " " << c << endl;
    //cout << a << " " << d << endl;

    return Rectangle(a, b, c, d);
}

void test_figures() {
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

int main()
{
    set <int*> banned_points;
    vector <Triangle> triangles;
    vector <Rectangle> rectangles;
    vector <Square> squares;
    vector <Elips> elipses;
    vector <Circle> circles;
    //int size = 6;
    int size = 200;
    char buf;
    int **points = new int* [size];

     
    ifstream input_file ("files/input1.dat");
    //ifstream input_file ("files/elips.txt");
    //ifstream input_file ("files/triangle.txt");
    //ifstream input_file ("files/data.txt");
    
    for (int i = 0; i < size; i++) {
        points[i] = new int[size];
        for (int j = 0; j < size; j++) {
            input_file >> buf;
            points[i][j] = int(buf - '0');
            cout << points[i][j];
            //cout << buf;
        }
        cout << endl;
    }

    bool flag = false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (points[i][j] == 1 && banned_points.find(&points[i][j]) == banned_points.end()) {
                if (is_elips(i, j, points, size)) {
                    //cout << "Is elips" << endl;
                    ban_points(i, j, points, size, banned_points);
                    //find_elips(i, j, points, size).show_points();
                }
                else if (is_rectangle(i, j, points, size)) {
                    ban_points(i, j, points, size, banned_points);
                    //cout << "Is rectangle" << endl;
                    //find_rect(i, j, points, size).show_points();
                }
                else if (is_triangle(i, j, points, size)) {
                    cout << "Is triangle" << endl;
                    cout << "i - " << i << " j - " << j << endl;
                    ban_points(i, j, points, size, banned_points);
                }
                else {
                    //cout << "Is noize" << endl;
                    ban_points(i, j, points, size, banned_points);
                }
            }   
            //if (flag) {
            //    find_rect(i, j, points, size).show_points();
            //    ban_points(i, j, points, size, banned_points);
            //    flag = false;
            //}
        }
    }

    for (auto r : rectangles) {
        r.show_points();
    }


    return 1;
}
