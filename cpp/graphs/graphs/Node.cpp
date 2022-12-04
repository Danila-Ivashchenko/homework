#include "Node.h"

using namespace std;

Node::Node(const int& aname) {
	name = aname;
}

void Node::addNeighbour(Node* neighbour) {
	neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
	neighbours.erase(neighbour);
}

void Node::print_neighbours() {
	for (node_iterator it = nb_begin(); it != nb_end(); it++) {
		cout << *this << " - " << **it << endl;
	}
	cout << endl;
}

void Node::write_neighbours(ofstream& outf) {
	for (node_iterator it = nb_begin(); it != nb_end(); it++) {
		outf << *this << " - " << **it << endl;
	}
}

ostream& operator << (ostream& out, const Node& node) {
	out << node.name << " ";
	return out;
}

ostream& operator <<(ostream& out, const Edge& ed) {
	out << ed.a << " " << ed.b;
	return out;
}

//ofstream& operator <<(ofstream& outf, const Node& node) {
//	outf << node.name << " ";
//	return outf;
//}