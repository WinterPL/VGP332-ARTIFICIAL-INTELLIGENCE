#include "Precompiled.h"
#include "Astar.h"

using namespace AI;

bool Astar::Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristics getH)
{
	//Reset everything
	graph.ResetSearchParameters();
	mOpenList.clear();
	mClosedList.clear();

	//add the start node to the open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;

	while (!mOpenList.empty() && !found)
	{
		auto currentNode = mOpenList.front();
		mOpenList.pop_front();

		if (currentNode->row == endY && currentNode->column == endX)
		{
			found = true;
		}
		//Expand the node list
		else
		{
			for (auto& neighbor : currentNode->neighbors)
			{
				if (neighbor == nullptr || !neighbor->opened)
					continue;

				if (!neighbor->opened)
				{
					neighbor->opened = true;
					neighbor->parent = currentNode;
					neighbor->g = currentNode->g + getCost(neighbor);
					neighbor->h = getH(neighbor, graph.GetNode(endX, endY));


					currentNode->g = getCost(currentNode);
					// TODO
					// Set the cost g
					//
					//insert in the open list
					//For Dijkstra just g-> Need to sort the open list -> for ASTAR related to g + h
					//Or
					//insert sorted
				}
				/*else if (newCost is cheaper)
				{
					// Do the edge relaxation
					//	update the parent
					//	use a newg that is cheaper
					//	resort the open list (For ASTAR you need to consider g + h)
					//	Heuristics in this case don't change! ->ASTAR
				}*/
			}
		}

		currentNode->opened = true;
		mClosedList.push_back(currentNode);

	}

	return found;
}