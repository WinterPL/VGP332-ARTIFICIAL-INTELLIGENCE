#include "Tilemap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int rows)
	{
		return x + (y * rows);
	}
}

void Tilemap::LoadTileMap(const char* tileMap)
{
	std::fstream file;
	file.open(tileMap, std::ios::in);

	assert(file.is_open());
	std::string line;

	std::getline(file, line, ' ');
	std::getline(file, line);
	mRows = atoi(line.c_str());

	std::getline(file, line, ' ');
	std::getline(file, line);
	mColumns = atoi(line.c_str());

	for (int i = 0; i < mColumns; i++) {
		getline(file, line);
		stringstream ss(line);
		string line;
		while (ss >> line) {
			mTileMap.push_back(stoi(line));

		}
	}

	file.close();
	assert(static_cast<int>(mTileMap.size()) == mRows * mColumns);

	mGridBasedGraph.Initialize(mRows, mColumns);

	auto GetNeighbor = [&](int x, int y) -> GridBasedGraph::Node*
	{
		auto node = mGridBasedGraph.GetNode(x, y);

		if (node == nullptr)
			return nullptr;

		if (IsBlocked(x, y))
			return nullptr;

		return node;
	};


	for (int y = 0; y < mColumns; y++)
	{
		for (int x = 0; x < mRows; x++)
		{
			if (!IsBlocked(x, y))
			{
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::East] = GetNeighbor(x + 1, y);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::West] = GetNeighbor(x - 1, y);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::North] = GetNeighbor(x, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::South] = GetNeighbor(x, y + 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthEast] = GetNeighbor(x + 1, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthWest] = GetNeighbor(x - 1, y - 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthEast] = GetNeighbor(x + 1, y + 1);
				mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthWest] = GetNeighbor(x - 1, y + 1);
			}
		}
	}
}

EMath::Vector2 Tilemap::GetPixelPosition(int x, int y) const
{
	return{ (x + 0.5f) * 32,(y + 0.5f) * 32 };
}

void Tilemap::FindPath(int startX, int startY, int endX, int endY, search type)
{
	startpX = startX; startpY = startY; endpX = endX; endpY = endY;
	NodeList closedList;

	switch (type) {
	case search::BfS:
	{
		BFS bfs;
		if (bfs.Run(mGridBasedGraph, startX, startY, endX, endY))
		{
			closedList = bfs.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->row, node->column));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
			mClosedList = bfs.GetClosedList();
		}
		else
		{
			mClosedList = bfs.GetClosedList();
		}
		break;
	}
	case search::DfS:
	{
		DFS dfs;
		if (dfs.Run(mGridBasedGraph, startX, startY, endX, endY))
		{
			closedList = dfs.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->row, node->column));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
			mClosedList = dfs.GetClosedList();
		}
		else
		{
			mClosedList = dfs.GetClosedList();
		}
		break;
	}
	case search::Dijikstra:
	{
		Dijkstra dijkstra;
		auto getCostWrapper = [&](const GridBasedGraph::Node* nodeA)
		{
			return GetCost(nodeA);
		};

		if (dijkstra.Run(mGridBasedGraph, startX, startY, endX, endY, getCostWrapper))
		{
			closedList = dijkstra.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->column, node->row));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
			mClosedList = dijkstra.GetClosedList();
		}
		else
		{
			mClosedList = dijkstra.GetClosedList();
		}
		break;
	}
	case search::AsTAR:
	{
		Astar astar;
		auto getCostWrapper = [&](const GridBasedGraph::Node* nodeA)
		{
			return GetCost(nodeA);
		};
		auto getHeuristicsWrapper = [&](const GridBasedGraph::Node* nodeA, const GridBasedGraph::Node* nodeB)
		{
			return GetCost(nodeA);
		};

		if (astar.Run(mGridBasedGraph, startX, startY, endX, endY, getCostWrapper, getHeuristicsWrapper))
		{
			closedList = astar.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->column, node->row));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
			mClosedList = astar.GetClosedList();
		}
		else
		{
			mClosedList = astar.GetClosedList();
		}
		break;
	}
	}
}


float Tilemap::GetCost(const AI::GridBasedGraph::Node* nodeA) const {
	const int tileIndex = ToIndex(nodeA->row, nodeA->column, mRows);
	return mTileTexture[mTileMap[(int)tileIndex]].weight;
}


void Tilemap::LoadTiles(const char* tilesPath)
{
	std::fstream file;
	file.open(tilesPath, std::ios::in);
	assert(file.is_open(), "File does not exist!");

	std::string line;
	std::string value;

	std::getline(file, line); //Read from file
	std::stringstream sStreamRows(line);
	std::getline(sStreamRows, value, ' ');
	std::getline(sStreamRows, value, '\n');

	int numberOfTiles = atoi(value.c_str());
	for (int i = 0; i < numberOfTiles; ++i)
	{
		std::getline(file, line);

		std::string path;
		std::string weightText;
		int weight;

		std::stringstream sStreamTile(line);
		std::getline(sStreamTile, path, ' ');
		std::getline(sStreamTile, weightText, '\n');

		weight = atoi(weightText.c_str());

		
		std::string tileFullPath = REng::ResourcesFullPath(path);
		Tile newTile;
		newTile.texture = LoadTexture(tileFullPath.c_str());
		newTile.weight = weight;
		mTileTexture.push_back(newTile);
	}

	file.close();
}

void Tilemap::Render()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);


	EMath::Vector2 position(0.0f, 0.0f);

	for (int y = 0; y < mColumns; ++y)
	{
		for (int x = 0; x < mRows; ++x)
		{
			int tileIndex = mTileMap[ToIndex(x, y, mRows)];
			DrawTexture(mTileTexture[tileIndex].texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			position.x += 32;
		}
		position.x = 0.0f;
		position.y += 32;
	}
}

void Tilemap::RenderLine() {
	const int tileSize = 32;
	EMath::Vector2 startingPosition(16, 16);
	float sX = startingPosition.x;
	float sY = startingPosition.y;
	for (int y = 0; y < mColumns; y++)
	{
		for (int x = 0; x < mRows; x++)
		{
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)sY, BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)sY, BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			if (mGridBasedGraph.GetNode(x, y)->neighbors[GridBasedGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			sX += 32;
		}
		sX = static_cast<float>(tileSize) * 0.5f;
		sY += tileSize;
	}


	for (auto& node : mClosedList)
	{
		if (node->parent)
		{
			EMath::Vector2 startP = GetPixelPosition(node->row, node->column);
			EMath::Vector2 endP = GetPixelPosition(node->parent->row, node->parent->column);
			DrawLine((int)startP.x, (int)startP.y, (int)endP.x, (int)endP.y, PINK);
		}
	}

	for (auto& i : path) {
		DrawCircle((int)i.x, (int)i.y, 10.0f, ORANGE);
	}

	EMath::Vector2 startP = GetPixelPosition(startpX, startpY);
	EMath::Vector2 endP = GetPixelPosition(endpX, endpY);
	DrawCircle((int)startP.x, (int)startP.y, 10.0f, GREEN);
	DrawCircle((int)endP.x, (int)endP.y, 10.0f, RED);
}

bool Tilemap::IsBlocked(int x, int y) const
{
	return mTileTexture[mTileMap[ToIndex(x, y, mRows)]].weight >= 5;
}

void Tilemap::cleanup() {
	for (auto& tt : mTileTexture)
	{
		UnloadTexture(tt.texture);
	}
}

