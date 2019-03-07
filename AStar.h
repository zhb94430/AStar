#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

class AStar
{
public:
	AStar();
	~AStar();

	std::vector<Node*> FindPath(Node* start, Node* end);
private:
};

std::vector<Node*> AStar::FindPath(Node* start, Node* end)
{
	std::vector<Node*> evaluated;
	std::vector<Node*> evaluating;
	std::vector<Node*> path;

	evaluating.push_back(start);

	while (!evaluating.empty)
	{
		Node* currentNode = // Sort evaluating by Node.nodeToGoalCost, pick the lowest one

		// Goal Check
		if (currentNode->isGoal)
		{
			return path;
		}

		evaluating.remove(currentNode);
		evaluated.push_back(currentNode);

		for (int i = 0; i < currentNode->paths.size; ++i)
		{
			Node* neighbor = currentNode->paths[i];

			if evaluated.contains(neighbor)
			{
				continue;
			}

			// Calculate a tentative score = costToNode + costBetween currentNode and Neighbor

			if !evaluating.contains(neighbor)
			{
				evaluating.push_back(neighbor);
			}
			else if (tentativeScore >= neighbor->startToNodeCost)
			{
				continue;
			}

			path.push_back(neighbor);
			// Record some scores
			// Might not needed if the graph already provides this data
		}
	}
}


#endif