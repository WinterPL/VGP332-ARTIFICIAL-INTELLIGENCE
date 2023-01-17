#pragma once
#include <iostream>  
#include<string>  
#include <REngine.h>
#include "AI.h"
using namespace std;

class Tilemap
{
public:
	struct Tile
	{
		Texture2D texture;
		int weight;
	};

	void LoadTileMap(const char* tileMap);
	void LoadTiles(const char* tilesPath);
	void Render();
	void cleanup();

	bool IsBlocked(int x, int y) const;

	std::vector<REng::Math::Vector2> FindPath(int startX, int startY, int endX, int endY);

private:
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;

	std::vector<int> mTileMap;
	std::vector<Tile> mTileTexture;

	AI::GridBaseGraph mGridBaseGraph;
	AI::NodeList mClosedList;
	int mRows;
	int mColumns;
};