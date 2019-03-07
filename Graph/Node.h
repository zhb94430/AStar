#ifndef NODE_H
#define NODE_H

#include <vector>

class Edge

class Node
{
public:
	Node();
	~Node();

private:
	std::vector<Node*> paths;

	char* nodeID;

	int startToNodeCost;
	int nodeToGoalCost;
};

#endif