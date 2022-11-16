#pragma once
#include <set>
#include <iostream>
#include <string>
#include "Node.h"



typedef std::set<Node*>::const_iterator
node_iterator;
class Graph {
	std::set<Node*> nodes;
public:
	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end);
	void removeEdge(Node* begin, Node* end);
	node_iterator begin() const {
		return nodes.begin();
	}
	node_iterator end() const { return nodes.end(); }
	void print_neighbours();
	bool in(const Node* node) {
		for (node_iterator it = begin(); it != end(); it++) {
			if ((*it)->name == node->name)
				return true;
		}
		return false;
	};
	Node* find(Node node) {
		for (node_iterator it = begin(); it != end(); it++) {
			if ((*it)->name == node.name)
				return *it;
		}
		return *end();
	}

	friend ostream& operator <<(ostream& out, const Graph& gr);
};

void Graph::addNode(Node* node) {
	nodes.insert(node);
}

void Graph::removeNode(Node* node) {
	nodes.erase(node);

	for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		(*it)->removeNeighbour(node);
	}
}

void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addNeighbour(end);
	end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
	if (end->neighbours.find(begin) == end->neighbours.end())
		return;
	if (begin->neighbours.find(end) == begin->neighbours.end())
		return;
	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}

ostream& operator<<(ostream& out, const Graph& gr)
{
	for (node_iterator it = gr.begin(); it != gr.end(); it++) {
		out << **it;
	}
	return out;
}

inline void Graph::print_neighbours(){
	for (node_iterator it = begin(); it != end(); it++)
		(*it)->print_neighbours();
}
