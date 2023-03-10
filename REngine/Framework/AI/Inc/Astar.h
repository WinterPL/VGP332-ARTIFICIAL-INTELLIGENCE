#pragma once

#include "GridBasedGraph.h"

namespace AI 
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(const GridBasedGraph::Node*)>;
	using GetHeuristics = std::function<float(const GridBasedGraph::Node*, const GridBasedGraph::Node*)>;
	class Astar
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristics getHeuristics);
		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}