#pragma once
#include <iostream>  
#include <string>  
#include <REngine.h>
#include "AI.h"

using namespace std;
class Character
{
public:
	void Init();
	void Update();
private:
	std::string fullpath;
	EMath::Vector2 position{ 200.f, 304.0f };
	Texture2D myTexture;
	Rectangle rect;
	float offsetY = 94;
	float offsetX = 80;
	int frame = 6;
	int currentFrame = 0;
	
	float animMaxTime = 0.1f;
	float currentTime = 0.0f;
};
