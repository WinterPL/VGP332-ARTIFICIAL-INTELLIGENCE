#pragma once
#include "Character.h"

using namespace REng;


void Character::Init() {
	fullpath = REng::ResourcesFullPath("hero_spritesheet.png");
	rect.x = 0.0f;
	rect.y = offsetY;
	rect.width = offsetX;
	rect.height = offsetY;

	myTexture = LoadTexture(fullpath.c_str());
}

void Character::Update() {
		float moveSpeed = 200.0f;
		if (IsKeyDown(KeyboardKey::KEY_RIGHT) && position.x < 1500.f) {
			position.x += moveSpeed * GetFrameTime();
			currentTime += GetFrameTime();
			if (currentTime > animMaxTime) {
				currentFrame++;
				currentFrame = currentFrame % frame;
				rect.x = currentFrame * offsetX;
				currentTime = 0.0f;
				rect.width = offsetX;
			}
			std::cout << position.x << " || " << position.y << std::endl;
		}
		if (IsKeyDown(KeyboardKey::KEY_LEFT) && position.x > 24.f) {
			position.x -= moveSpeed * GetFrameTime();
			currentTime += GetFrameTime();
			if (currentTime > animMaxTime) {
				currentFrame++;
				currentFrame = currentFrame % frame;
				rect.x = currentFrame * offsetX;
				currentTime = 0.0f;
				rect.width = -offsetX;
			}
		}
		if (IsKeyDown(KeyboardKey::KEY_UP) && position.y > 15.f) {
			position.y -= moveSpeed * GetFrameTime();
			
		}
		if (IsKeyDown(KeyboardKey::KEY_DOWN) && position.y < 770.f) {
			position.y += moveSpeed * GetFrameTime();
		}
	
	DrawTextureRec(myTexture, rect, {position.x,position.y}, WHITE);
}