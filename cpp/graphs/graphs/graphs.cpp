#include <iostream>
#include <string>;
#include <fstream>
#include <vector>
#include "Graph.h"

using namespace std;

struct Edge{
    Node a;
    Node b;
    Edge(int aa, int ab) {
        a.name = aa;
        b.name = ab;
    };
};
ostream& operator <<(ostream& out, const Edge& ed) {
    out << ed.a << " " << ed.b;
    return out;
}

int main()
{
    vector <Edge> arr;
    Graph gr;

    ifstream file("testgraph.txt");

    string buf, buf1;
    file >> buf >> buf1;
    cout << buf << " " << buf1;
    int a, b;
    while (file >> a >> b) {
        Edge ptr(a, b);
        arr.push_back(ptr);
    }

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << endl;
        if (!gr.in(&arr[i].a))
            gr.addNode(&arr[i].a);
        if (!gr.in(&arr[i].b))
            gr.addNode(&arr[i].b);
        gr.addEdge(gr.find(arr[i].a), gr.find(arr[i].b));
    }
    gr.print_neighbours();

    cout << endl << gr << endl;




    return 10;
}