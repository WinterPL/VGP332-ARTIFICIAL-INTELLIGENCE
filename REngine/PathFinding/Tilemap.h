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

	enum class search {
		DfS,
		BfS,
		Dijikstra,
		AsTAR
	};

	void LoadTileMap(const char* tileMap);
	void LoadTiles(const char* tilesPath);
	void Render();
	void cleanup();

	bool IsBlocked(int x, int y) const;
	void FindPath(int startX, int startY, int endX, int endY, search type);

	float GetCost(const AI::GridBaseGraph::Node* nodeA) const;


private:
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;

	std::vector<int> mTileMap;
	std::vector<Tile> mTileTexture;

	AI::GridBaseGraph mGridBaseGraph;
	AI::NodeList mClosedList;
	int mRows;
	int mColumns;

	int startpX, startpY, endpX, endpY;
	std::vector<REng::Math::Vector2> path;
};