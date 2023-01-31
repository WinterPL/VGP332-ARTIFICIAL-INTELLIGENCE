#include "Precompiled.h"
#include "Dijkstra.h"

using namespace AI;

bool Dijkstra::Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost)
{
	//Reset everything
	graph.ResetSearchParameters();
	mOpenList.clear();
	mClosedList.clear();

	//add the start node to the opem list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;
	int cost;

	while (!mOpenList.empty() && !found)
	{
		auto currentNode = mOpenList.front();
		mOpenList.pop_front();
		if (currentNode->row == endX && currentNode->column == endY) {
			found = true;
		}
		else {
			for (auto neighbore : currentNode->neighbors) {
				if (neighbore == nullptr || !neighbore->opened)continue;
				if (!neighbore->opened) {
					neighbore->opened = true;
					neighbore->parent = currentNode;

					currentNode->g = getCost(currentNode);
					// TODO
						// Set the cost g
						//
						//insert in the open list
						//For Dijkstra just g-> Need to sort the open list -> for ASTAR related to g + h
						//Or
						//insert sorted
					mOpenList.push_back(neighbore);
					mOpenList.sort([](GridBaseGraph::Node* lhs, GridBaseGraph::Node* rhs) {return lhs->g < rhs->g; });		
				}
				else if (neighbore->g > (currentNode->g + getCost(neighbore)))
				{
					neighbore->parent = currentNode;
					neighbore->g = currentNode->g + getCost(neighbore);

					// Do the edge relaxation
					//	update the parent
					//	use a newg that is cheaper
					//	resort the open list (For ASTAR you need to consider g + h)
					//	Heuristics in this case don't change! ->ASTAR
					mOpenList.sort([](GridBaseGraph::Node* lhs, GridBaseGraph::Node* rhs) {return lhs->g < rhs->g; });
				}
			}
		}
		mClosedList.push_back(currentNode);
	}
	return found;

}