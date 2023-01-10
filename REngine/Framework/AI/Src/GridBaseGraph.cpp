#include "Precompiled.h"
#include "GridBaseGraph.h"

namespace AI {
	void GridBaseGraph::initialize(int columns, int rows) {

	}

	GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y) {

		return nullptr;
	}
	const GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y)const {
		return nullptr;
	}

	int GridBaseGraph::GetColumns()const {
		return mColumns;
	}
	int GridBaseGraph::GetRows()const {
		return mRows;
	}

	int GridBaseGraph::GetIndex(int x, int y) const {
		return 0;
	}
}
