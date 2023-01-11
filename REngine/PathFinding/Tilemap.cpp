#include "Tilemap.h"

namespace {
	inline int ToinDex(int x, int y, int columns) {
		return x + (y * columns);
	}
}

void Tilemap::LoadTileMap(const char* tileMap, int tileSize) {
    string line;
    fstream file(tileMap);
    getline(file, line, ':');
    getline(file, line);
    mRows = stoi(line);
    getline(file, line, ':');
    getline(file, line);
    mColumns = stoi(line);

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
}

void Tilemap::LoadTiles(const char* tilepath) {
    fstream file(tilepath);
    string line;
    while (!file.eof())
    {
        Texture2D tempTexture;
        std::string fullpath;
        getline(file, line, ' ');
        //std::cout << line << endl;
        REng::ResourcesFullPath(line, fullpath);
        tempTexture = LoadTexture(fullpath.c_str());
        mTileMapTextures.push_back(tempTexture);
        getline(file, line);
        //std::cout << line << endl;
    }
	
}

void Tilemap::Render() {
	//implement
    int x = 0, y = 0, row = 0;
    for (int i = 0; i < mTileMap.size(); i++) {
        switch (mTileMap[i]) {
        case 0:
            DrawTexture(mTileMapTextures[0], x, y, WHITE);
            break;
        case 1:
            DrawTexture(mTileMapTextures[1], x, y, WHITE);
            break;
        case 2:
            DrawTexture(mTileMapTextures[2], x, y, WHITE);
            break;
        case 3:
            DrawTexture(mTileMapTextures[3], x, y, WHITE);
            break;
        case 4:
            DrawTexture(mTileMapTextures[4], x, y, WHITE);
            break;
        case 5:
            DrawTexture(mTileMapTextures[5], x, y, WHITE);
            break;
        case 6:
            DrawTexture(mTileMapTextures[6], x, y, WHITE);
            break;
        case 7:
            DrawTexture(mTileMapTextures[7], x, y, WHITE);
            break;
        case 8:
            DrawTexture(mTileMapTextures[8], x, y, WHITE);
            break;
        case 9:
            DrawTexture(mTileMapTextures[9], x, y, WHITE);
            break;
        case 10:
            DrawTexture(mTileMapTextures[10], x, y, WHITE);
            break;
        }
        x += 32;
        row++;
        if(row == mRows){
            y += 32;
            x = 0;
            row = 0;
        }
        //DrawLine();
    }
}

void Tilemap::cleanup() {
    for(auto& tt : mTileMapTextures)
    {
        UnloadTexture(tt);
    }
}