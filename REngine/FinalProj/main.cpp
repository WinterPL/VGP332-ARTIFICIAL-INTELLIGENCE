#include <REngine.h>
#include "Tilemap.h"

using namespace REng;

Tilemap myTileMap;

void GameInit()
{
	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");

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
	REng::Start("MyFinalProj");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}