#pragma once
#include <REngine.h>
#include "AI.h"

using namespace std;

class Tilemap
{
public :
	void LoadTileMap(const char* tileMap, int tileSize);
	void LoadTiles(const char* tilepath);
	void Render();
	void cleanup();

private:
	std::vector<int> mTileMap = {};
	std::vector<pair<Texture2D,int>> mTileMapTextures;

	AI::GridBaseGraph mGridBaseGraph;

	bool done = true;
	int mRows;
	int mColumns;
	int mTileSize;
};

