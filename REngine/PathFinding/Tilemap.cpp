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
	std::string value;

	std::getline(file, line);
	std::stringstream sStreamRows(line);
	std::getline(sStreamRows, value, ' ');
	std::getline(sStreamRows, value, '\n');

	mRows = atoi(value.c_str());

	std::getline(file, line);
	std::stringstream sStreamColumns(line);
	std::getline(sStreamColumns, value, ' ');
	std::getline(sStreamColumns, value, '\n');

	mColumns = atoi(value.c_str());

	while (std::getline(file, line) && line != "")
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
	}

	file.close();
	assert(static_cast<int>(mTileMap.size()) == mRows * mColumns);

	mGridBaseGraph.Initialize(mRows, mColumns);

	auto GetNeighbor = [&](int x, int y) -> GridBaseGraph::Node*
	{
		auto node = mGridBaseGraph.GetNode(x, y);

		if (node == nullptr)
			return nullptr;

		if (IsBlocked(x, y))
			return nullptr;

		return node;
	};


		for (int x = 0; x < mColumns; ++x)
	{
	for (int y = 0; y < mRows; ++y)
		{
			auto currentTile = mTileTexture[mTileMap[ToIndex(x, y, mColumns)]];
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

	for (int y = 0; y < mRows; ++y)
	{
		int tileIndex = 0;
		for (int x = 0; x < mColumns; ++x)
		{
			tileIndex = mTileMap[ToIndex(x, y, mColumns)];
			auto backGroundTile = std::find_if(mTileTexture.begin(), mTileTexture.end(), [](const Tile& tile) {return tile.weight == 0; });

			DrawTexture(backGroundTile->texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			if (tileIndex != 0)
			{
				DrawTexture(mTileTexture[tileIndex].texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
			}
			position.x += mTileTexture[tileIndex].texture.width;
		}
		position.x = 0.0f;
		position.y += mTileTexture[tileIndex].texture.height;
	}


	const int tileSize = 32;
	constexpr float halfSize = static_cast<float>(tileSize) * 0.5f;
	REng::Math::Vector2 startingPosition(halfSize, halfSize);
	float sX = startingPosition.x;
	float sY = startingPosition.y;
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)sY, BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
			sX += static_cast<float>(tileSize);
		}
		sX = static_cast<float>(tileSize) * 0.5f;
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