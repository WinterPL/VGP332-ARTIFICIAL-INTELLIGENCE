#pragma once
#include <REngine.h>
#include "AI.h"

using namespace std;
using namespace AI;

class Tilemap
{
public :
	void LoadTileMap(const char* tileMap);
	void LoadTiles(const char* tilepath);
	void Render();
	void cleanup();

	bool IsBlock(int x, int y) const;

	std::vector<REng::Math::Vector2> FindPath(int startX, int startY, int endX, int endY);
private:
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;
	std::vector<int> mTileMap = {};
	std::vector<pair<Texture2D,int>> mTileMapTextures;

	AI::GridBaseGraph mGridBaseGraph;

	bool done = true;
	int mRows;
	int mColumns;
	int mTileSize;
};

