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
				}


			}
		}

		}
	return found;

}