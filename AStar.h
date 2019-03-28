#ifndef ASTAR_H
#define ASTAR_H

#include <algorithm>
#include <vector>

#include "Graph/Node.h"

class AStar
{
public:
	int (*HeuristicFunction)(Node*, std::vector<Node*>);

	AStar() { HeuristicFunction = AStar::DefaultHeuristic; }
	~AStar();

	std::vector<Node*> FindPath(Node* start, Node* end);
	bool NodeCompare(Node* node1, Node* node2);
	int DefaultHeuristic(Node* node);
private:

};

int DefaultHeuristic(Node* node, std::vector<Node*> currentPath)
{
	Node* currentNode = node;
	int distanceTaken = 0;

	for (int i = currentPath.size()-1; i >= 0; i-- )
	{
		Edge* currentEdge = &std::find(currentNode->paths.begin(), currentNode->paths.end(), Edge(currentNode, currentPath[i]));

		distanceTaken += currentEdge->cost;
	}

	int totalCost = distanceTaken + node->estimatedCost;

	return totalCost;
}

bool NodeCompare(Node* node1, Node* node2)
{
	return (HeuristicFunction(node1) - HeuristicFunction(node2)) > 0;
}

std::vector<Node*> AStar::FindPath(Node* start, Node* end)
{
	std::vector<Node*> evaluated;
	std::vector<Node*> evaluating;
	std::vector<Node*> path;

	evaluating.push_back(start);

	while (!evaluating.empty)
	{
		// Sort evaluating by lowest combined score
		std::sort(evaluating.begin(), evaluating.end(), NodeCompare);

		Node* currentNode = evaluating[0];// pick the lowest one

		// Goal Check
		if (currentNode->isGoal)
		{
			return path;
		}

		evaluating.remove(currentNode);
		evaluated.push_back(currentNode);

		// Iterate through each neighbor, filter out the evaluated ones
		for (int i = 0; i < currentNode->paths.size; ++i)
		{
			Node* neighbor = currentNode->paths[i]->end;

			if (evaluated.contains(neighbor))
			{
				continue;
			}

			if (!evaluating.contains(neighbor))
			{
				evaluating.push_back(neighbor);
			}
		}
	}
}


#endif