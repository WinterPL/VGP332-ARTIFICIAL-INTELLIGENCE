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
	return 0;
}