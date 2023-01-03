#pragma once
#include <vector>
#include <string>
#include <REngine.h>

class Tilemap
{
public :
	void LoadTileMap(const char* tileMap, int tileSize);
	void LoadTiles(const char* tilepath);
	void Render();

private:
	std::vector<int> mTileMap;
	std::vector<Texture2D> mTileMapTextures;
	int mRows;
	int mColomns;
	int mTileSize;
};

