#pragma once
#include "GridBaseGraph.h"

namespace AI {
	using NodeList = std::list<GridBaseGraph::Node*>;
	class BFS {
	public:
		bool Run(const GridBaseGraph& graph, int startX, int startY, int endX, int endY);
		
	private:
		
	};




}