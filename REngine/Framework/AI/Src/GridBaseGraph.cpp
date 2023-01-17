#include "Precompiled.h"
#include "GridBaseGraph.h"

namespace AI {

	void GridBaseGraph::initialize(int rows, int columns) {
		/*mNodes.clear();

		mNodes.resize(columns);
		for (auto& row : mNodes)
			row.resize(rows);

		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				mNodes[i][j] = Node(j, i);

				if (i != 0) mNodes[i][j].neighbors[(int)Directions::North] = &mNodes[i - 1][j];
				if (i != columns - 1) mNodes[i][j].neighbors[(int)Directions::South] = &mNodes[i + 1][j];
				if (j != rows - 1) mNodes[i][j].neighbors[(int)Directions::East] = &mNodes[i][j + 1];
				if (i != 0 && j != 0) mNodes[i][j].neighbors[(int)Directions::West] = &mNodes[i][j - 1];
				if (i != 0 && j != rows - 1) mNodes[i][j].neighbors[(int)Directions::NorthEast] = &mNodes[i - 1][j + 1];
				if (i != columns - 1 && j != rows - 1) mNodes[i][j].neighbors[(int)Directions::SouthEast] = &mNodes[i + 1][j + 1];
				if (i != 0 && j != 0) mNodes[i][j].neighbors[(int)Directions::NorthWest] = &mNodes[i - 1][j - 1];
				if (i != columns - 1 && j != 0) mNodes[i][j].neighbors[(int)Directions::SouthWest] = &mNodes[i + 1][j - 1];
			}
		}*/
		mRows = rows; mColumns = columns;
		mNodes.resize(mRows * mColumns);
		for (int y = 0; y < mRows; ++y){
			for (int x = 0; x < mColumns; ++x){
				mNodes[GetIndex(x, y)].column = x;
				mNodes[GetIndex(x, y)].row = y;
			}
		}
	}

	void GridBaseGraph::ResetSearchParameter() {
		for (auto& node : mNodes)
		{
			node.parent = nullptr;
			node.opened = false;
			node.closed = false;
		}
	}


	GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y) {
		/*if (y >= mNodes.size() || x >= mNodes.front().size()) { return nullptr; }
		return &mNodes[x][y];*/
		if (x < 0 || x >= mColumns || y < 0 || y >= mRows) {return nullptr;}
		const int index = GetIndex(x, y);
		return &mNodes[index];
	}
	const GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y)const {
		/*if (y >= mNodes.size() || x >= mNodes.front().size()) { return nullptr; }
		return &mNodes[x][y];*/
		if (x < 0 || x >= mColumns || y < 0 || y >= mRows) { return nullptr; }
		const int index = GetIndex(x, y);
		return &mNodes[index];
	}

	int GridBaseGraph::GetColumns()const {
		return mColumns;
	}
	int GridBaseGraph::GetRows()const {
		return mRows;
	}

	int GridBaseGraph::GetIndex(int x, int y) const {
		return x + (y * mColumns);
	}
}
