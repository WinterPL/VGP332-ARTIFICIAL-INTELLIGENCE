#include "Tilemap.h"

namespace {
	inline int ToinDex(int x, int y, int columns) {
		return x + (y * columns);
	}
}

void Tilemap::LoadTileMap(const char* tileMap, int tileSize) {

	//implement
}

void Tilemap::LoadTiles(const char* tilepath) {

	//implement
	Texture2D tempTexture;
	std::string fullpath;
	REng::ResourcesFullPath("hero_spritesheet.png", fullpath);
	tempTexture = LoadTexture(fullpath.c_str());
	mTileMapTextures.push_back(tempTexture);
}

void Tilemap::Render() {
	//implement
}