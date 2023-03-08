#pragma once
#include <iostream>  
#include <string> 

#include <REngine.h>
#include "AI.h"

using namespace std;
class NPC
{
	enum class state {
		goHome,
		stayHome,
		goMine,
		Mining,
		goSaloon,
		Drinking
	};

public:
	void Init(float x, float y,string name, Color c);
	void Update();
private:
	std::string fullpath;
	EMath::Vector2 position{ 0,0};
	EMath::Vector2 positionHome{ 0,0};
	EMath::Vector2 positionMine{ 1175.f, 304.0f };
	EMath::Vector2 positionSaloon{ 736.f, 660.0f };
	Texture2D myTexture;
	Rectangle rect;
	float offsetY = 94;
	float offsetX = 80;
	int frame = 6;
	int currentFrame = 0;

	float animMaxTime = 0.1f;
	float currentTime = 0.0f;
	state mState = state::goMine;

	int mGold = 0;
	int mEnergy = 100;
	int mHunger = 100;
	float cd = 0;
	float getTHING = 0;

	EMath::Vector2 agentToDestination{0,0};
	float distance;

	string Name;
	Color mColor;
};

