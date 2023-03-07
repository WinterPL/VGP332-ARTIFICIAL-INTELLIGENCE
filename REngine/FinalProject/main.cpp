#include <REngine.h>
#include "Tilemap.h"

using namespace REng;

Tilemap myTileMap;

int startX = 10, startY = 10; int endX = 15, endY = 5;

void GameInit()
{

	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");
	myTileMap.FindPath(startX, startY, endX, endY, Tilemap::search::BfS);

}

bool GameUpdate()
{
	myTileMap.Render();

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	myTileMap.cleanup();
}

void RenderDebugUI()
{

}

int main()
{
	REng::Start("MyPathfinding");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}