#ifndef ASTAR_H
#define ASTAR_H

#include <algorithm>
#include <vector>

#include "Graph/Node.h"

int DefaultHeuristic(Node* node, std::vector<Node*> path)
{
	Node* currentNode = node;
	int distanceTaken = 0;

	for (int i = path.size()-1; i >= 0; i-- )
	{
		Edge* currentEdge = &*std::find(currentNode->paths.begin(), currentNode->paths.end(), Edge(currentNode, path[i]));

		distanceTaken += currentEdge->cost;
	}

	int totalCost = distanceTaken + node->estimatedCost;

	return totalCost;
}

class AStar
{
public:
	std::vector<Node*> path;
	int (*HeuristicFunction)(Node* , std::vector<Node*>); // Heuristic Function Pointer

	std::vector<Node*> FindPath(Node* start, Node* end);
	static bool NodeCompare(Node* node1, Node* node2);

	AStar() { HeuristicFunction = &DefaultHeuristic; }
	~AStar();
private:

};

bool AStar::NodeCompare(Node* node1, Node* node2)
{
	return (HeuristicFunction(node1, path) - HeuristicFunction(node2, path)) > 0;
}

std::vector<Node*> AStar::FindPath(Node* start, Node* end)
{
	std::vector<Node*> evaluated = std::vector<Node*>();
	std::vector<Node*> evaluating = std::vector<Node*>();
	std::vector<Node*> path = std::vector<Node*>();

	evaluating.push_back(start);

	while (!evaluating.empty())
	{
		// Sort evaluating by lowest combined score
		std::sort(evaluating.begin(), evaluating.end(), AStar::NodeCompare);

		Node* currentNode = evaluating[0];// pick the lowest one

		// Goal Check
		if (currentNode == end)
		{
			return path;
		}

		// Find and remove idiom
		evaluating.erase(std::remove(evaluating.begin(), evaluating.end(), currentNode), evaluating.end());
		
		evaluated.push_back(currentNode);

		// Iterate through each neighbor, filter out the evaluated ones
		for (int i = 0; i < currentNode->paths.size(); ++i)
		{
			Node* neighbor = currentNode->paths[i].end;

			if ( std::find(evaluated.begin(), evaluated.end(), neighbor) != evaluated.end() )
			{
				continue;
			}

			if ( !(std::find(evaluating.begin(), evaluating.end(), neighbor) != evaluating.end()))	
			{
				evaluating.push_back(neighbor);
			}
		}
	}
}


#endif