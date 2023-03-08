#include <REngine.h>
#include "Tilemap.h"
#include "Character.h"

using namespace REng;

Tilemap myTileMap;
Character myCharacter;

void GameInit()
{
	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");
	myTileMap.FindPath(7, 11, 37, 11, Tilemap::search::BfS);
	myCharacter.Init();
}

bool GameUpdate()
{
	myTileMap.Render();
	myTileMap.RenderLine();
	myCharacter.Update();

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