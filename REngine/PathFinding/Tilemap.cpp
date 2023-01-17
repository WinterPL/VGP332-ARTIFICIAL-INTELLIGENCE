#include "Tilemap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
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
	//cout << mRows << endl;

	std::getline(file, line, ' ');
	std::getline(file, line);
	mColumns = atoi(line.c_str());
	//cout << mColumns << endl;

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

	mGridBaseGraph.Initialize(mRows, mColumns);

	auto GetNeighbor = [&](int x, int y) -> GridBaseGraph::Node*
	{
		auto node = mGridBaseGraph.GetNode(x, y);

		if (node == nullptr) { return nullptr; }
		if (IsBlocked(x, y)) { return nullptr; }

		return node;
	};


	for (int y = 0; y < mColumns; ++y)
	{
		for (int x = 0; x < mRows; ++x)
		{
			//auto currentTile = mTileMap[mTileMap[ToIndex(x, y, mColumns)]];
			if (!IsBlocked(x, y))
			{
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::East] = GetNeighbor(x + 1, y);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::West] = GetNeighbor(x - 1, y);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::North] = GetNeighbor(x, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::South] = GetNeighbor(x, y + 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::NorthEast] = GetNeighbor(x + 1, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::NorthWest] = GetNeighbor(x - 1, y - 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::SouthEast] = GetNeighbor(x + 1, y + 1);
				mGridBaseGraph.GetNode(x, y)->neighbors[(int)GridBaseGraph::SouthWest] = GetNeighbor(x - 1, y + 1);
			}
		}
	}
}

REng::Math::Vector2 Tilemap::GetPixelPosition(int x, int y) const
{
	return
	{
		(x + 0.5f) * 32,
		(y + 0.5f) * 32
	};
}

std::vector<REng::Math::Vector2> Tilemap::FindPath(int startX, int startY, int endX, int endY)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;

	BFS bfs;
	if (bfs.Run(mGridBaseGraph, startX, startY, endX, endY))
	{
		closedList = bfs.GetClosedList();
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
		mClosedList = bfs.GetClosedList();
	}

	return path;
}


void Tilemap::LoadTiles(const char* tilesPath)
{
	//Implement this
	std::fstream file;
	file.open(tilesPath, std::ios::in);
	assert(file.is_open(), "File does not exist!");

	std::string line;

	std::getline(file, line, ' ');
	std::getline(file, line);

	int numberOfTiles = atoi(line.c_str());
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
	int i = 0;
	for (int y = 0; y < mColumns; y++)
	{
		for (int x = 0; x < mRows; x++)
		{
				DrawTexture(mTileTexture[mTileMap[i]].texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			position.x += 32;
			i++;
		}
		position.x = 0.0f;
		position.y += 32;
	}


	const int tileSize = 32;

	float sX = 16;
	float sY = 16;
	for (int y = 0; y < mColumns; ++y)
	{
		for (int x = 0; x < mRows; ++x)
		{
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + tileSize), (int)(sY - tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - tileSize), (int)(sY - tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + tileSize), (int)(sY + tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - tileSize), (int)(sY + tileSize), BLACK); }
			sX += tileSize;
		}
		sX = 16;
		sY += tileSize;
	}

}

void Tilemap::cleanup() {
	for (auto& tt : mTileTexture)
	{
		UnloadTexture(tt.texture);
	}
}


bool Tilemap::IsBlocked(int x, int y) const
{
	return mTileTexture[mTileMap[ToIndex(x, y, mColumns)]].weight >= 5;
}