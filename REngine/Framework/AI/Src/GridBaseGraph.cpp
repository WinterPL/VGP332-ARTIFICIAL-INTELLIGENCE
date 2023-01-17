#include "Precompiled.h"
#include "GridBaseGraph.h"

namespace AI {

	void GridBaseGraph::Initialize(int rows, int columns)
	{
		//TODO
		//Resize mNodes to the matching dimension
		//for each node, set it's attributes (row / collumn)
		mRows = rows;
		mColumns = columns;
		mNodes.resize(mRows * mColumns);

		for (int y = 0; y < mColumns; ++y)
		{
			for (int x = 0; x < mRows; ++x)
			{
				mNodes[GetIndex(x, y)].row = x;
				mNodes[GetIndex(x, y)].column = y;
			}
		}
	}

	void GridBaseGraph::ResetSearchParameters()
	{
		for (auto& node : mNodes)
		{
			node.parent = nullptr;
			node.opened = false;
			node.closed = false;
		}
	}

	GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y)
	{
		if (x < 0 || x >= mRows || y < 0 || y >= mColumns)
		{
			return nullptr;
		}
		const int index = GetIndex(x, y);
		return &mNodes[index];
	}

	const GridBaseGraph::Node* GridBaseGraph::GetNode(int x, int y) const
	{
		if (x < 0 || x >= mRows || y < 0 || y >= mColumns)
		{
			return nullptr;
		}
		const int index = GetIndex(x, y);
		return &mNodes[index];
	}

	int GridBaseGraph::GetColumns() const
	{
		return mColumns;
	}

	int GridBaseGraph::GetRows() const
	{
		return mRows;
	}

	int GridBaseGraph::GetIndex(int x, int y) const
	{
		return x + (y * mRows);
	}
}