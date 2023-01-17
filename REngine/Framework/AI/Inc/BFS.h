#pragma once

#include "GridBaseGraph.h"

namespace AI
{
	using NodeList = std::list<GridBaseGraph::Node*>;
	class BFS
	{
	public:
		bool Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY);
		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}