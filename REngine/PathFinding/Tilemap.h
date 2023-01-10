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
	AI::GridBaseGraph mGridBaseGrahp;
	std::vector<int> mTileMap;
	std::vector<Texture2D> mTileMapTextures;

	int mRows;
	int mColumns;
	int mTileSize;
};

