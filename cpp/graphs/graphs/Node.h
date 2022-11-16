#pragma once
#include "Graph.h"
#include <iostream>

using namespace std;


//class Node {
//	std::string name;
//	std::set<Node*> neighbours;
//	void addNeighbour(Node* neighbour);
//	void removeNeighbour(Node* neighbour);
//public:
//	Node(const std::string& aname) : name(aname) {}
//	const std::string& getName() const { return name; }
//	std::set<Node*>::const_iterator nb_begin() const {
//		return neighbours.begin();
//	}
//	std::set<Node*>::const_iterator nb_end() const { return neighbours.end(); }
//	friend class Graph;
//};

class Node {
	int name;
	set<Node*> neighbours;
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
public:
	Node(const int& aname) : name(aname) {}
	Node() : name(0) {}
	const int& getName() const { return name; }
	set<Node*>::const_iterator nb_begin() const {
		return neighbours.begin();
	}
	set<Node*>::const_iterator nb_end() const { return neighbours.end(); }
	void print_neighbours();
	Node(const Node& node) {
		name = node.name;
	}

	friend class Graph;
	friend ostream& operator <<(ostream& out, const Node& node);
	friend struct Edge;
};

void Node::addNeighbour(Node* neighbour) {
	neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
	neighbours.erase(neighbour);
}

ostream& operator << (ostream& out, const Node& node) {
	out << node.name << " ";
	return out;
}

inline void Node::print_neighbours(){
	for (set<Node*>::const_iterator it = nb_begin(); it != nb_end(); it++) {
		cout << *this << " - " << **it << endl;
	}
	cout << endl;
}



