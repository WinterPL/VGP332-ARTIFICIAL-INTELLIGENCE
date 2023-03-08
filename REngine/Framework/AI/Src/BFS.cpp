#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
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

		mClosedList.push_back(mOpenList.front());
		for (const auto& neighbore : mOpenList.front()->neighbors) {
			if (!neighbore || neighbore->opened)continue;
			neighbore->opened = true;
			neighbore->parent = mOpenList.front();
			mOpenList.push_back(neighbore);
		}
		mOpenList.pop_front();
		found = ((mClosedList.back()->row == endX) && (mClosedList.back()->column == endY));
	}
	return found;

}