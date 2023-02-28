#include <REngine.h>
#include <AI.h>

#include "Spaceship.h"

//wander globals
float wanderRadius = 5.0f;
float wanderDistance = 5.0f;
float wanderJitter = 5.0f;

namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Spaceship> spaceship;
}

void GameInit()
{
	world = std::make_unique<AI::AIWorld>();
	spaceship = std::make_unique<Spaceship>(*world.get());

	spaceship->Load();
	spaceship->position = { 100.0f, 100.0f };
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	
	if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
	{
		const float mouseX = GetMousePosition().x;
		const float mouseY = GetMousePosition().y; 
		spaceship->destination = EMath::Vector2(mouseX, mouseY);
	}

	spaceship->Update(deltaTime);
	spaceship->Render();

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	spaceship->Unload();
}

void RenderDebugUI()
{
	ImGui::Begin("Steering Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	
	
	ImGui::End();
}

int main()
{
	REng::Start("Steering Behaviors");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}