#ifndef NODE_H
#define NODE_H

#include <limits>
#include <vector>

class Node;

class Edge
{
public:
	int cost;
	Node* start;
	Node* end;

	Edge();
	Edge(Node* _start, Node* _end) { start = _start; end = _end; cost = std::numeric_limits<double>::quiet_NaN(); }
	Edge(Node* _start, Node* _end, int _cost) { start = _start; end = _end; cost = _cost; }
	~Edge();

private:
};

class Node
{
public:
	std::string name;
	std::vector<Edge> paths;
	int estimatedCost;

	Node();
	Node(std::string _name, int _estimatedCost) {name = _name; estimatedCost = _estimatedCost; }
	Node(std::string _name, int _estimatedCost,std::vector<Edge> _paths) { paths = _paths; Node(_name, _estimatedCost); }
	~Node();

private:
};

#endif