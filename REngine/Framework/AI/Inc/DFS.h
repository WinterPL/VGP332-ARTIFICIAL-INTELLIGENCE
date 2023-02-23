#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	class DFS
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY);
		const std::list<GridBasedGraph::Node*>& GetClosedList() const { return mClosedList; }

	private:
		std::stack<GridBasedGraph::Node*> mOpenList;
		std::list<GridBasedGraph::Node*> mClosedList;
	};
}
