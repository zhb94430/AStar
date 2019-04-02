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

	bool operator==(const Edge& e)
	{
		return (start == e.start) && (end == e.end);
	}

	// Return the other end of the edge
	Node* otherEnd(Node* input);

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

private:
};

class Graph
{
public:
	std::vector<Node*> nodes;

	Graph();
	Graph(std::vector<Node*> _nodes) { nodes = _nodes; }
};

Node* Edge::otherEnd(Node* input)
{
	if (start == input)
	{
		return end;
	}

	else if (end == input)
	{
		return start;
	}

	return NULL;
}

#endif