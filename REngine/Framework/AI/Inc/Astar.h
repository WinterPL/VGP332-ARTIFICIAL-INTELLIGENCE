#pragma once

#include "GridBaseGraph.h"

namespace AI 
{
	using NodeList = std::list<GridBaseGraph::Node*>;
	using GetCost = std::function<float(const GridBaseGraph::Node*)>;
	using GetHeuristics = std::function<float(const GridBaseGraph::Node*, const GridBaseGraph::Node*)>;
	class Astar
	{
	public:
		bool Run(GridBaseGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristics getHeuristics);
		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}