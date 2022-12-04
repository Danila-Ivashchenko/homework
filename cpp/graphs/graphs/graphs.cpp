#include <iostream>
#include <string>
#include <fstream>
#include "Graph.h"

using namespace std;

bool in_vector(const Node& node, const vector <Node>& nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        if (node == nodes[i])
            return true;
    }
    return false;
}

void write_islands(vector <set <Node*>>& islands) {
    string filename = "island";
    int n = 0;
    for (auto island : islands) {
        string ntxt = ".txt";
        ntxt = char(n + '0') + ntxt;
        string new_filename = filename + ntxt;
        ofstream file(new_filename);
        cout << ntxt << endl;
        cout << file.good() << endl;
        for (auto node : island) {
            node->write_neighbours(file);
        }
        file.close();
        n++;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    vector <Edge> arr;
    vector <Node> nodes;
    Graph gr;
    string test1 = "testgraph.txt";
    string test2 = "test.txt";
    string test3 = "1000.csv";
    ifstream file(test3);

    string buf, buf1;
    file >> buf >> buf1;

    int a, b;
    int n = 0;

    cout << "Заполение рёбер из файла" << endl;
    while (file >> a >> b) {
        Edge ptr(a, b);
        arr.push_back(ptr);
        if (!in_vector(arr[n].a, nodes))
            nodes.push_back(arr[n].a);
        if (!in_vector(arr[n].b, nodes))
            nodes.push_back(arr[n].b);
        n++;
    }

    cout << "Разбиение рёбер на вершины" << endl;
    for (int i = 0; i < nodes.size() - 1; i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            if (nodes[j] < nodes[i]) {
                Node tmp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = tmp;
            }
        }
    }

    cout << "Внесение вершин в граф" << endl;
    for (int i = 0; i < nodes.size(); i++)
        gr.addNode(&nodes[i]);

    cout << "Внесение рёбер в граф" << endl;
    for (int i = 0; i < arr.size(); i++) {
        gr.addEdge(gr.find(arr[i].a), gr.find(arr[i].b));
    }

    //cout << gr << endl;

    //cout << gr.DFS(nodes[0], nodes[1]) << endl;

    //for (auto island : gr.find_islands()) {
    //    for (auto node : island) {
    //        node->print_neighbours();

    //    }
    //    cout << endl;
    //}
    cout << "Поиск островов" << endl;
    vector <set <Node*>> islands = gr.find_islands();
    cout << "Количество островов: " << islands.size() << endl;
    write_islands(islands);

    return 0;
}