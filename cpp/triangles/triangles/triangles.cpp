#include <iostream>
#include <fstream>
#include "geometry.h"
#include "file.h"

using namespace std;

int main()
{
    ifstream input("files/test2.txt");
    int n = 36;
    Point* points = new Point[n];
    Triangle* triangles = new Triangle[n];
    Triangle tr;
    Point buf;
    double max_area[3];
    int index_i[3], index_j[3], index_k[3];
       
    for (int i = 0; i < n; i++) {
        input >> buf;
        points[i] = buf;
        cout << points[i] << endl;
    }

    for (int i = 0; i < 3; i++)
        max_area[i] = 0;

    for (int i = 0; i < n - 2; i++) {
        tr.vertex[0] = points[i];
        for (int j = 0; j < n - 1; j++) {
            tr.vertex[1] = points[j];
            for (int k = 0; k < n; k++) {
                tr.vertex[2] = points[k];
                //cout << tr.vertex[0] << ' ' << tr.vertex[1] << ' ' << tr.vertex[2] << endl;
                //cout << calc_area_triangle(tr) << endl;
                if (max_area[2] <= calc_area_triangle(tr)){
                    max_area[2] = calc_area_triangle(tr);
                    index_i[2] = i;
                    index_j[2] = j;
                    index_k[2] = k;
                }
                else if (max_area[1] <= calc_area_triangle(tr)) {
                    max_area[1] = calc_area_triangle(tr);
                    index_i[1] = i;
                    index_j[1] = j;
                    index_k[1] = k;
                }
                else if (max_area[0] <= calc_area_triangle(tr)) {
                    max_area[0] = calc_area_triangle(tr);
                    index_i[0] = i;
                    index_j[0] = j;
                    index_k[0] = k;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        cout << max_area[i] << endl;
        cout << points[index_i[i]] << '\t' << points[index_j[i]] << '\t' << points[index_k[i]] << endl;
    }
    
    input.close();
    return 102;
}