#include "Graph.h"

using namespace std;

typedef set<Node*>::const_iterator
node_iterator;
void Graph::addNode(Node* node) {
	nodes.insert(node);
}

void Graph::removeNode(Node* node) {
	nodes.erase(node);

	for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
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

inline void Graph::print_neighbours() {
	for (node_iterator it = begin(); it != end(); it++)
		(*it)->print_neighbours();
}

Node* Graph::find(const Node& node) {
	for (node_iterator it = begin(); it != end(); it++) {
		if ((*it)->name == node.name)
			return *it;
	}
	return *end();
};

bool Graph::BFS(Node& begin_node, Node& end_node) {
	//cout << "Ну ищем" << endl;
	queue<Node*> not_visited;
	not_visited.push(&begin_node);
	set<Node*> visited;
	while (!not_visited.empty()) {
		Node* next = not_visited.front();
		not_visited.pop();
		if (end_node.name == next->name)
			return true;
		visited.insert(next);
		for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++)
			if (visited.find(*it) == visited.end())
				not_visited.push(*it);
	}
	return false;
};

bool Graph::DFS(Node& begin_node, Node& end_node) {
	stack<Node*> not_visited;
	not_visited.push(&begin_node);
	set<Node*> visited;
	while (!not_visited.empty()) {
		Node* next = not_visited.top();
		not_visited.pop();
		if (end_node == *next)
			return true;
		visited.insert(next);
		for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++)
			if (visited.find(*it) == visited.end())
				not_visited.push(*it);
	}
	return false;
};

vector<set <Node*>> Graph::find_islands() {
	int counter = 0;
	vector <set <Node*>> islands;
	set<Node*> added;
	for (auto it_b = begin(); it_b != end(); it_b++) {
		if (added.find(*it_b) == added.end()) {
			set<Node*> island;
			island.insert(*it_b);
			for (auto it_e = begin(); it_e != end(); it_e++) {
				if (added.find(*it_e) == added.end()) {
					if (it_b != it_e) {
						if (BFS(**it_b, **it_e)) {
							island.insert(*it_e);
							added.insert(*it_e);
						}
					}
				}
			}
			islands.push_back(island);
		}
	}
	return islands;
};

