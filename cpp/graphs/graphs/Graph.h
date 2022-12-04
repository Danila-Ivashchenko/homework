#pragma once

#include <set>
#include <iostream>
#include <fstream>
#include "Node.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Node;

typedef set<Node*>::const_iterator node_iterator;
class Graph {
	set<Node*> nodes;
public:
	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end);
	void removeEdge(Node* begin, Node* end);
	node_iterator begin() const {
		return nodes.begin();
	};
	node_iterator end() const { return nodes.end(); }
	void print_neighbours();
	Node* find(const Node& node);

	bool BFS(Node& begin_node, Node& end_node);
	bool DFS(Node& begin_node, Node& end_node);
	vector<set <Node*>> find_islands();

	friend ostream& operator <<(ostream& out, const Graph& gr);
};
