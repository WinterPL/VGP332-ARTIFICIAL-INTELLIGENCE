#include <REngine.h>
#include "Tilemap.h"

REng::Math::Vector2 position(0.0f, 0.);
Texture2D myTexture;
Rectangle rect;
float offsetY = 94;
float offsetX = 80;
int frame = 6;
int currentFrame = 0;

float animMaxTime = 0.1f;
float currentTime = 0.0f;

using namespace REng;

Tilemap myTileMap;

void GameInit()
{
	/*{std::string fullpath;
	REng::ResourcesFullPath("hero_spritesheet.png", fullpath);
	rect.x = 0.0f;
	rect.y = offsetY;
	rect.width = offsetX;
	rect.height = offsetY;

	myTexture = LoadTexture(fullpath.c_str());
	}*/

	myTileMap.LoadTiles("tiles.txt");
	myTileMap.LoadTileMap("tilemap.txt");
}

bool GameUpdate()
{
	myTileMap.Render();
	//{//movement
	//	float moveSpeed = 200.0f;
	//	if (IsKeyDown(KeyboardKey::KEY_RIGHT)) {
	//		position.x += moveSpeed * GetFrameTime();
	//		currentTime += GetFrameTime();
	//		if (currentTime > animMaxTime) {
	//			currentFrame++;
	//			currentFrame = currentFrame % frame;
	//			rect.x = currentFrame * offsetX;
	//			currentTime = 0.0f;
	//			rect.width = offsetX;
	//		}
	//	}
	//	if (IsKeyDown(KeyboardKey::KEY_LEFT)) {
	//		position.x -= moveSpeed * GetFrameTime();
	//		currentTime += GetFrameTime();
	//		if (currentTime > animMaxTime) {
	//			currentFrame++;
	//			currentFrame = currentFrame % frame;
	//			rect.x = currentFrame * offsetX;
	//			currentTime = 0.0f;
	//			rect.width = -offsetX;
	//		}
	//	}
	//	if (IsKeyDown(KeyboardKey::KEY_UP)) {
	//		position.y -= moveSpeed * GetFrameTime();
	//	}
	//	if (IsKeyDown(KeyboardKey::KEY_DOWN)) {
	//		position.y += moveSpeed * GetFrameTime();
	//	}
	//}
	//DrawTextureRec(myTexture, rect, {position.x,position.y}, WHITE);


	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	myTileMap.cleanup();
}

void RenderDebugUI()
{
	//ImGui::ShowDemoWindow();
	//ImGui::Begin("myimguiWindow");
	//ImGui::End();
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