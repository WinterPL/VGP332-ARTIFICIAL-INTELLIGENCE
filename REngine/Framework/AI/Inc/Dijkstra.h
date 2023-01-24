#pragma once

#include "GridBaseGraph.h"

namespace AI
{
	using NodeList = std::list<GridBaseGraph::Node*>;
	using GetCost = std::function<float(const GridBaseGraph::Node*)>;
	class Dijkstra
	{
	public:
		bool Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost);
		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}