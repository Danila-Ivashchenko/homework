#include <iostream>
#include <fstream>
#include "file.h"
#include "geometry.h"

using namespace std;

int main()
{
    ifstream file("tests/test3.txt");
    if (!file.is_open()) return -1;
    int points_num = 8;
    Point* points = new Point[points_num];
    Triangle tr, max_trs[3];
    double max_area = 0;
 
    Point test_p;
 
    read_points(file, points, points_num);

    for (int i = 0; i < points_num - 2; i++) {
        for (int j = i + 1; j < points_num - 1; j++) {
            for (int c = j + 1; c < points_num; c++) {
                tr.set_coords(points[i], points[j], points[c]);
                tr.calc_area(); 
                for (int tr_id = 0; tr_id < 3; tr_id++) {
                    if (tr.area > max_trs[tr_id].area) {
                        max_trs[tr_id] = tr;
                        break;
                    }
                }
                tr.clear();
            }
        }
    }

    ofstream outf("output3.txt");
    
    for (auto tr : max_trs) {
        outf << tr << endl;
        cout << tr << endl;
    }

    outf.close();
    return 10;
}
