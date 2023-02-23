#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO
	//Resize mNodes to the matching dimension
	//for each node, set it's attributes (row / collumn)
	mRows = rows;
	mColumns = columns;
	mNodes.resize(mRows * mColumns);

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mRows; ++x)
		{
			mNodes[GetIndex(x, y)].column = x;
			mNodes[GetIndex(x, y)].row = y;
		}
	}
}

void GridBasedGraph::ResetSearchParameters()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.opened = false;
		node.closed = false;
		node.g = 0.0f;
		node.h = 0.0f;
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}
	const int index = GetIndex(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}
	const int index = GetIndex(x, y);
	return &mNodes[index];
}

int GridBasedGraph::GetColumns() const
{
	return mColumns;
}

int GridBasedGraph::GetRows() const
{
	return mRows;
}

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}