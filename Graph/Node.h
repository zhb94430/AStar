#ifndef NODE_H
#define NODE_H

#include <vector>

class Node;

class Edge
{
public:
	int cost;
	Node* start;
	Node* end;

	Edge();
	Edge(Node* _start, Node* _end, int _cost) { start = _node1; end = _end; cost = _cost; }
	~Edge();

private:
}

class Node
{
public:
	string name;
	std::vector<Edge> paths;
	int estimatedCost;

	Node();
	Node(string _name, int _estimatedCost) {name = _name; estimatedCost = _estimatedCost; }
	Node(string _name, int _estimatedCost,std::vector<Edge> _paths) { paths = _paths; Node(string _name, int _estimatedCost); }
	~Node();

private:
};

#endif