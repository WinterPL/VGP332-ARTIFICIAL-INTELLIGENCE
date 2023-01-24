#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

bool BFS::Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY)
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

	//TODO
	//		while end node not reached && open list isn't empty:
	//			select node N from open list ----> Depend on your startegy
	//			if node is end
	//				found = true
	//			else expand node N :
	//				if expanded node isn't in open list nor closed list
	//					add expanded node to open list, set parent
	//			Add node N to closed list
	while (!mOpenList.empty() && !found)
	{
		/*auto currentNode = mOpenList.front();
		mOpenList.pop_front();
		if (currentNode->row == endX && currentNode->column == endY) {
			found = true;
		}
		else {
			for (auto neighbore : currentNode->neighbors) {
				if (neighbore != nullptr && !neighbore->opened && !neighbore->closed) {
					neighbore->parent = currentNode;
					neighbore->closed = true;
				}
			}
		}
		currentNode->closed = true;
		mClosedList.push_back(currentNode);*/

		//--Another
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