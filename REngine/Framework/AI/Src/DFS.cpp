#include "Precompiled.h"
#include "DFS.h"

using namespace AI;

bool DFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	graph.ResetSearchParameters();
	auto node = graph.GetNode(startX, startY);

	mClosedList.push_back(node);
	mOpenList.push(node);
	node->opened = true;

	bool found = false;
	while (!mOpenList.empty() && !found) {
		bool unVisited = false;
		for (auto& neighbore : mOpenList.top()->neighbors) {
			if (!neighbore || neighbore->opened)continue;
			neighbore->opened = true;
			neighbore->parent = mOpenList.top();
			mClosedList.push_back(neighbore);
			mOpenList.push(neighbore);
			unVisited = true;
			break;
		}
		if (mClosedList.back()->row == endX && mClosedList.back()->column == endY) {found = true;}
		if (!unVisited) { mOpenList.pop(); }
	}

	return found;
}