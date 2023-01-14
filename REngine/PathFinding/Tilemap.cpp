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

    mGridBaseGrahp.initialize(mRows,mColumns);

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
        getline(file, line);
        int i = stoi(line);
        //std::cout << line << endl;
        mTileMapTextures.push_back(make_pair(tempTexture,i));
    }
	
}

void Tilemap::Render() {
	//implement
    int x = 0, y = 0, row = 0;
    for (int i = 0; i < mTileMap.size(); i++) {
        switch (mTileMap[i]) {
        case 0:
            DrawTexture(mTileMapTextures[0].first, x, y, WHITE);
            break;
        case 1:
            DrawTexture(mTileMapTextures[1].first, x, y, WHITE);
            break;
        case 2:
            DrawTexture(mTileMapTextures[2].first, x, y, WHITE);
            break;
        case 3:
            DrawTexture(mTileMapTextures[3].first, x, y, WHITE);
            break;
        case 4:
            DrawTexture(mTileMapTextures[4].first, x, y, WHITE);
            break;
        case 5:
            DrawTexture(mTileMapTextures[5].first, x, y, WHITE);
            break;
        case 6:
            DrawTexture(mTileMapTextures[6].first, x, y, WHITE);
            break;
        case 7:
            DrawTexture(mTileMapTextures[7].first, x, y, WHITE);
            break;
        case 8:
            DrawTexture(mTileMapTextures[8].first, x, y, WHITE);
            break;
        case 9:
            DrawTexture(mTileMapTextures[9].first, x, y, WHITE);
            break;
        case 10:
            DrawTexture(mTileMapTextures[10].first, x, y, WHITE);
            break;
        }
        x += 32;
        row++;
        if(row == mRows){
            y += 32;
            x = 0;
            row = 0;
        }
        

        int Xpos = 16;
        int Ypos = 16;
        int rt = 0;
        int ct = 0;
        for(int i : mTileMap)
        {
            if (mTileMap[i + 1] <= 5 && rt<=48) {
                DrawLine(Xpos, Ypos, Xpos+32, Ypos, WHITE);
            }
            if (mTileMap[i + 50] <= 5 && rt <= 50 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos, Ypos+32, WHITE);
            }
            if (mTileMap[i + 51] <= 5 && rt <= 48 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos+32, Ypos + 32, WHITE);
            }
            if (mTileMap[i + 49] <= 5 && rt != 0 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos - 32, Ypos + 32, WHITE);
            }
            Xpos += 32;
            rt++;
            if (rt ==50) {
                Ypos += 32;
                Xpos = 16;
                rt = 0;
                ct++;
            }
        }
    }
}

void Tilemap::cleanup() {
    for(auto& tt : mTileMapTextures)
    {
        UnloadTexture(tt.first);
    }
}