#include "Tilemap.h"

namespace {
	inline int ToinDex(int x, int y, int columns) {
		return x + (y * columns);
	}
}

void Tilemap::LoadTileMap(const char* tileMap, int tileSize) {
    string line;
    int width = 0;
    fstream file(tileMap);
    getline(file, line, ':');
    getline(file, line);
    mRows = stoi(line);
    getline(file, line, ':');
    getline(file, line);
    mColumns = stoi(line);

    for (int i = 0; i < mColumns; i++) {
        getline(file, line);
        for (int i = 0; i < line.size(); i++) {
            mTileMap.push_back(line[i]-48);
            width++;
        }
    }

    file.close();
}

void Tilemap::LoadTiles(const char* tilepath) {

	//implement
    fstream file(tilepath);
    string line;
    while (!file.eof())
    {
        Texture2D tempTexture;
        std::string fullpath;
        getline(file, line);
        REng::ResourcesFullPath(line, fullpath);
        tempTexture = LoadTexture(fullpath.c_str());
        mTileMapTextures.push_back(tempTexture);
    }
	
}

void Tilemap::Render() {
	//implement
}

void Tilemap::cleanup() {
    for(Texture2D tt : mTileMapTextures)
    {
        UnloadTexture(tt);
    }
}