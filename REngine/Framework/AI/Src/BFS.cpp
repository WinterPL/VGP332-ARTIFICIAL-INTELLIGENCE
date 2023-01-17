#include "Precompiled.h"
#include "BFS.h"

namespace AI {
	bool BFS::Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY) {
		graph.ResetSearchParameter();
		mOpenList.clear();
		mClosedList.clear();
		
		auto node = graph.GetNode(startX, startY);
		mOpenList.push_back(node);
		node->opened = true;

		bool found = false;


		return found;
	}

}