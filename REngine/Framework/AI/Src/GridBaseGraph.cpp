#include "Precompiled.h"
#include "GridBaseGraph.h"

namespace AI {
	void GridBaseGraph::initialize(int rows, int columns) {
		mNodes.resize(columns);
		for (auto& r : mNodes) {
			r.resize(rows);
		}

		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				mNodes[i][j] = Node(j,i);


			}
		}


	}

	GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y) {
		if (y >= mNodes.size() || x >= mNodes.front().size()) { return nullptr; }
		return &mNodes[x][y];

	}
	const GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y)const {
		if (y >= mNodes.size() || x >= mNodes.front().size()) { return nullptr; }
		return &mNodes[x][y];
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
