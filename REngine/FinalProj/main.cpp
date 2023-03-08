#include <REngine.h>
#include "Tilemap.h"
#include "Character.h"
#include "NPC.h"

using namespace REng;

Tilemap myTileMap;
Character myCharacter;
NPC npc1;
NPC npc2;
NPC npc3;
NPC npc4;
NPC npc5;
NPC npc6;
NPC npc7;

void GameInit()
{
	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");
	//myTileMap.FindPath(7, 11, 37, 11, Tilemap::search::BfS);
	myCharacter.Init();
	npc1.Init(200.f, 304.0f, "Tommy",RED);
	npc2.Init(330.f, 595.0f, "Angelo",GREEN);
	npc3.Init(1155.f, 650.0f, "Marcus",BLUE);
	npc4.Init(680.f, 95.0f, "Polymore",YELLOW);
	npc5.Init(740.f, 760.0f, "Party",BROWN);
	npc6.Init(970.f, 460.0f, "Tanachai",LIME);
	npc7.Init(1315.f, 185.0f, "Peekis",GRAY);
}

bool GameUpdate()
{
	myTileMap.Render();
	//myTileMap.RenderLine();
	//myCharacter.Update();
	npc1.Update();
	npc2.Update();
	npc3.Update();
	npc4.Update();
	npc5.Update();
	npc6.Update();
	npc7.Update();

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