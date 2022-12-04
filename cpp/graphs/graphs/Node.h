#pragma once
#include "Graph.h"


using namespace std;

class Node;

typedef set<Node*>::const_iterator node_iterator;
class Node {
	int name;
	set<Node*> neighbours;
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
public:
	Node(const int& aname);
	Node() : name(0) {};

	node_iterator nb_begin() const {
		return neighbours.begin();
	};
	node_iterator nb_end() const { return neighbours.end(); }
	Node(const Node& node) {
		name = node.name;
	};

	void print_neighbours();
	void write_neighbours(ofstream& outf);


	friend bool operator == (Node fnode, Node snode) { return fnode.name == snode.name; };
	friend bool operator < (Node fnode, Node snode) { return fnode.name < snode.name; };
	friend class Graph;
	friend ostream& operator <<(ostream& out, const Node& node);
	friend ofstream& operator <<(ofstream& outf, const Node& node) {
		outf << node.name;
		return outf;
	};
	friend struct Edge;
};

struct Edge {
	Node a;
	Node b;
	Edge(int aa, int ab) {
		a.name = aa;
		b.name = ab;
	};
};



