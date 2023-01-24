#pragma once

#include "GridBaseGraph.h"

namespace AI
{
	class DFS
	{
	public:
		bool Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY);
		const std::list<GridBaseGraph::Node*>& GetClosedList() const { return mClosedList; }

	private:
		std::stack<GridBaseGraph::Node*> mOpenList;
		std::list<GridBaseGraph::Node*> mClosedList;
	};
}
