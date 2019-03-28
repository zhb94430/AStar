#ifndef ASTAR_H
#define ASTAR_H

#include <algorithm>
#include <vector>
#include <unordered_map>

#include "Graph/Node.h"

class AStar
{
public:
	struct NodeCostPair
	{
		Node* node;
		int totalCost;

		bool operator<(const NodeCostPair& n) const 
		{
			return totalCost < n.totalCost;
		}

		bool operator==(const NodeCostPair& n) const
		{
			return (node == n.node) && (totalCost == n.totalCost);
		}
	};

	std::unordered_map<Node*, Node*> previousNodeLookup;
	std::unordered_map<Node*, int> currentCostLookup;
	// int (*HeuristicFunction)(Node*); // Heuristic Function Pointer

	std::vector<Node*> FindPath(Node* start, Node* end);

	AStar() { /*HeuristicFunction = &DefaultHeuristic;*/ }
	~AStar();
private:
	std::vector<Node*> ReconstructPathFrom(Node* end);

};

std::vector<Node*> AStar::FindPath(Node* start, Node* end)
{
	std::vector<Node*> evaluated = std::vector<Node*>();
	std::vector<NodeCostPair> evaluating = std::vector<NodeCostPair>();

	evaluating.push_back((NodeCostPair){start, 0});

	while (!evaluating.empty())
	{
		// Sort evaluating by lowest combined score
		std::sort(evaluating.begin(), evaluating.end());

		NodeCostPair* currentNodePair = &evaluating[0];// pick the lowest one

		// Goal Check
		if (currentNodePair->node == end)
		{
			return ReconstructPathFrom(end);
		}

		// Find and remove idiom
		evaluating.erase(std::remove(evaluating.begin(), evaluating.end(), *currentNodePair), evaluating.end());
		evaluated.push_back(currentNodePair->node);

		// Iterate through each neighbor, filter out the evaluated ones
		for (int i = 0; i < currentNodePair->node->paths.size(); ++i)
		{
			Edge* edgeToNeighbor = &currentNodePair->node->paths[i];
			Node* neighborNode = edgeToNeighbor->end;
			int neighborCost = currentCostLookup[currentNodePair->node] + edgeToNeighbor->cost;

			// If the neighbor does not have a cost recorded
			// or if the current neighbor cost is less than recorded cost
			// and if neighbor is not visited
			if ((currentCostLookup.find(neighborNode) == currentCostLookup.end() ||
				neighborCost < currentCostLookup[neighborNode]) &&
				!(std::find(evaluated.begin(), evaluated.end(), neighborNode) != evaluated.end()))
			{
				currentCostLookup[neighborNode] = neighborCost;
				int totalCost = neighborCost + neighborNode->estimatedCost;

				evaluating.push_back((NodeCostPair){neighborNode, neighborCost});

				//Record Path
				previousNodeLookup[neighborNode] = currentNodePair->node;
			}
		}
	}
}

std::vector<Node*> AStar::ReconstructPathFrom(Node* end)
{
	Node* currentNode = end;
	Node* previousNode = previousNodeLookup[currentNode];

	std::vector<Node*> path;

	while (previousNode != currentNode)
	{
		path.push_back(currentNode);

		currentNode = previousNode;
		previousNode = previousNodeLookup[currentNode];
	}

	std::reverse(path.begin(), path.end());

	return path;
}

#endif