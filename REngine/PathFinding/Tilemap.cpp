#include "Tilemap.h"

namespace {
	inline int ToinDex(int x, int y, int columns) {
		return x + (y * columns);
	}
}


void Tilemap::LoadTileMap(const char* tileMap) {
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
            mTileMap.push_back((int)stoi(line));
            //cout << line << endl;
        }
    }

    file.close();
    assert(static_cast<int>(mTileMap.size()) == mRows*mColumns);

    mGridBaseGraph.initialize(mRows,mColumns);
    
    auto GetNeighbor = [&](int x, int y)->GridBaseGraph::Node* {
        auto node = mGridBaseGraph.GetNode(x, y);

        if (node == nullptr) { return nullptr; }
        if (IsBlock(x, y)) { return nullptr; }

        return node;
    };
    
    for (int y = 0; y < mRows; ++y) {
        for (int x = 0; x < mColumns; ++x) {
            auto currentTile = mTileMapTextures[mTileMap[ToinDex(x, y, mColumns)]].second;
            if (!IsBlock(x, y)) {
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East] = GetNeighbor(x+1,y);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West] = GetNeighbor(x-1,y);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North] = GetNeighbor(x,y-1);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South] = GetNeighbor(x,y+1);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast] = GetNeighbor(x+1,y-1);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest] = GetNeighbor(x-1,y-1);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast] = GetNeighbor(x+1,y+1);
                mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest] = GetNeighbor(x+1,y-1);
            }
        }
    }


}

std::vector<REng::Math::Vector2> Tilemap::FindPath(int startX, int startY, int endX, int endY) {
    std::vector<REng::Math::Vector2> path;
    NodeList closedList;

    BFS bfs;

    if (bfs.Run(mGridBaseGraph, startX, startY, endX, endY)) {
        closedList = bfs.GetClosedList();

        auto node = closedList.back();
        while (node != nullptr)
        {
            path.push_back(GetPixelPosition(node->column,node->row));
            node = node->parent;
        }
        std::reverse(path.begin(), path.end());
    }
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
    {//DRAW
    int x = 0, y = 0, row = 0;
    for (int i = 0; i < mTileMap.size(); i++) {
        /* //hard code 
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
        }*/
        DrawTexture(mTileMapTextures[mTileMap[i]].first, x, y, WHITE);
        x += mTileMapTextures[mTileMap[i]].first.width;
        row++;
        if (row == mRows) {
            y += mTileMapTextures[mTileMap[i]].first.height;
            x = 0;
            row = 0;
            }
         }
    }

    const int tileSize = 32;
    REng::Math::Vector2 startingPosition(static_cast<float>(tileSize) * 0.5f, static_cast<float>(tileSize) * 0.5f);
    float sX = startingPosition.x;
    float sY = startingPosition.y;
    for (int y = 0; y < mRows; ++y) {
        for (int x = 0; x < mRows; ++x) {
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::East]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)sY, BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::West]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)sY, BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::North]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY - (float)tileSize), BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::South]) { DrawLine((int)sX, (int)sY, (int)sX, (int)(sY + (float)tileSize), BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::NorthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY - (float)tileSize), BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthEast]) { DrawLine((int)sX, (int)sY, (int)(sX + (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
            if (mGridBaseGraph.GetNode(x, y)->neighbors[GridBaseGraph::SouthWest]) { DrawLine((int)sX, (int)sY, (int)(sX - (float)tileSize), (int)(sY + (float)tileSize), BLACK); }
        }
        sX = static_cast<float>(tileSize) * 0.5f;
        sY += tileSize;
    }


       /* int Xpos = 16;
        int Ypos = 16;
        int rt = 0;
        int ct = 0;
        for (int i : mTileMap) {
            if (mTileMap[i + 1] <= 5 && rt <= 48) {
                DrawLine(Xpos, Ypos, Xpos + 32, Ypos, RED);
            }
            if (mTileMap[i + 50] <= 5 && rt <= 50 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos, Ypos + 32, WHITE);
            }
            if (mTileMap[i + 51] <= 5 && rt <= 48 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos + 32, Ypos + 32, BLUE);
            }
            if (mTileMap[i + 49] < 5 && rt > 0 && ct <= 26) {
                DrawLine(Xpos, Ypos, Xpos - 32, Ypos + 32, GREEN);
            }
            
            Xpos += 32;
            rt++;
            if (rt ==50) {
                Ypos += 32;
                Xpos = 16;
                rt = 0;
                ct++;
            }
        }*/
}

void Tilemap::cleanup() {
    for(auto& tt : mTileMapTextures)
    {
        UnloadTexture(tt.first);
    }
}

bool Tilemap::IsBlock(int x, int y)const {
    return mTileMapTextures[mTileMap[ToinDex(x, y, mColumns)]].second >= 5;
}

REng::Math::Vector2 Tilemap::GetPixelPosition(int x, int y)const {
    return {(x+0.5f)*mTileSize,(y+0.5f)*mTileSize};
}
