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

	std::getline(file, line,' ');
	std::getline(file, line);
	mColumns = atoi(line.c_str());

	/*while (std::getline(file, line) && line != "")
	{
		std::string lineString = line;
		while (!lineString.empty())
		{
			size_t pos = lineString.find(" ");
			std::string tileValue = lineString.substr(0, pos);
			size_t prevSize = lineString.size();
			lineString = lineString.substr(pos + 1);
			size_t newSize = lineString.size();
			mTileMap.push_back(atoi(tileValue.c_str()));
			if (prevSize == newSize)
			{
				break;
			}
		}
	}*/
	for (int i = 0; i < mColumns; i++) {
		getline(file, line);
		stringstream ss(line);
		string line;
		while (ss >> line) {
			mTileMap.push_back(stoi(line));
			//cout << line << endl;
		}
	}

	file.close();
	assert(static_cast<int>(mTileMap.size()) == mRows * mColumns);

	mGridBaseGraph.Initialize(mRows,mColumns);

	auto GetNeighbor = [&](int x, int y) -> GridBaseGraph::Node*
	{
		auto node = mGridBaseGraph.GetNode(x, y);

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
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East] = GetNeighbor(x + 1, y);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West] = GetNeighbor(x - 1, y);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North] = GetNeighbor(x, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South] = GetNeighbor(x, y + 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast] = GetNeighbor(x + 1, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest] = GetNeighbor(x - 1, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast] = GetNeighbor(x + 1, y + 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest] = GetNeighbor(x - 1, y + 1);
			}
		}
	}
}

REng::Math::Vector2 Tilemap::GetPixelPosition(int x, int y) const
{
	return{(x + 0.5f) * 32,(y + 0.5f) * 32};
}

std::vector<REng::Math::Vector2> Tilemap::FindPath(int startX, int startY, int endX, int endY, search type)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;

	switch (type) {
	case search::BfS:
		{
			BFS bfs;
			if (bfs.Run(mGridBaseGraph, startX, startY, endX, endY))
			{
				closedList = bfs.GetClosedList();
				auto node = closedList.back();
				while (node != nullptr)
				{
					path.push_back(GetPixelPosition(node->row, node->column));
					node = node->parent;
				}
				std::reverse(path.begin(), path.end());
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
			if (dfs.Run(mGridBaseGraph, startX, startY, endX, endY))
			{
				closedList = dfs.GetClosedList();
				auto node = closedList.back();
				while (node != nullptr)
				{
					path.push_back(GetPixelPosition(node->row, node->column));
					node = node->parent;
				}
				std::reverse(path.begin(), path.end());
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
			auto getCostWrapper = [&](const GridBaseGraph::Node* nodeA)
			{
				return GetCost(nodeA);
			};

			if (dijkstra.Run(mGridBaseGraph, startX, startY, endX, endY, getCostWrapper))
			{
				closedList = dijkstra.GetClosedList();
				auto node = closedList.back();
				while (node != nullptr)
				{
					path.push_back(GetPixelPosition(node->column, node->row));
					node = node->parent;
				}
				std::reverse(path.begin(), path.end());
			}
			else
			{
				mClosedList = dijkstra.GetClosedList();
			}
			break;
		}
	}

	return path;
}

std::vector<REng::Math::Vector2> Tilemap::FindDijikstra(int startX, int startY, int endX, int endY) {
	
}

float Tilemap::GetCost(const AI::GridBaseGraph::Node* nodeA) const{
	const int tileIndex = ToIndex(nodeA->row, nodeA->column, mRows);
	return mTileTexture[mTileMap[tileIndex]].weight;
}


void Tilemap::LoadTiles(const char* tilesPath)
{
	//Implement this
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

		std::string tileFullPath;
		REng::ResourcesFullPath(path, tileFullPath);
		Tile newTile;
		newTile.texture = LoadTexture(tileFullPath.c_str());
		newTile.weight = weight;
		mTileTexture.push_back(newTile);
	}

	file.close();
}

void Tilemap::Render()
{
	REng::Math::Vector2 position(0.0f, 0.0f);

	for(int y = 0; y < mColumns; ++y)
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

	const int tileSize = 32;
	REng::Math::Vector2 startingPosition(16,16);
	float sX = startingPosition.x;
	float sY = startingPosition.y;
	for (int y = 0; y < mColumns; y++)
	{
		for (int x = 0; x < mRows; x++)
		{
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			sX += 32;
		}
		sX = static_cast<float>(tileSize) * 0.5f;
		sY += tileSize;
	}


	for (auto i : mClosedList)
	{
		if(i->parent != nullptr)
		{
		DrawLine(i->row, i->column, i->parent->row, i->parent->column, RED);
		}
	}

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