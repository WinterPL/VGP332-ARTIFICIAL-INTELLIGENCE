#pragma once
#include "NPC.h"


using namespace REng;

void NPC::Init(float x, float y, string name,Color c) {

	position = { x,y };
	positionHome = { x,y };
	Name = name;
	mColor = c;
	fullpath = REng::ResourcesFullPath("hero_spritesheet.png");
	rect.x = 0.0f;
	rect.y = offsetY;
	rect.width = offsetX;
	rect.height = offsetY;

	myTexture = LoadTexture(fullpath.c_str());
}

void NPC::Update() {
	float moveSpeed = 150.0f;
	switch (mState) {
	case state::goHome:
		agentToDestination = positionHome - position;
		distance = EMath::Magnitude(agentToDestination);
		if (distance > 10.0f)
		{
			currentTime += GetFrameTime();
			if (currentTime > animMaxTime) {
				currentFrame++;
				currentFrame = currentFrame % frame;
				rect.x = currentFrame * offsetX;
				currentTime = 0.0f;
				rect.width = offsetX;
			}
			const auto direction = agentToDestination / distance;
			EMath::Vector2 velocity = direction * moveSpeed;
			position += velocity * GetFrameTime();
		}
		else {
			cd = 15;
			mState = state::stayHome;
		}
		DrawText("Go Home", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	case state::stayHome:
		cd -= GetFrameTime();
		getTHING -= GetFrameTime();
		if (getTHING <= 0) {
			mHunger -= 2;
			getTHING = 1;
		}

		if (cd <= 0) {
			mEnergy = 100;
			getTHING = 1;
			mState = state::goMine;
		}
		DrawText("STAY HOME", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	case state::goMine:
		agentToDestination = positionMine - position;
		distance = EMath::Magnitude(agentToDestination);
		if (distance > 10.0f)
		{
			currentTime += GetFrameTime();
			if (currentTime > animMaxTime) {
				currentFrame++;
				currentFrame = currentFrame % frame;
				rect.x = currentFrame * offsetX;
				currentTime = 0.0f;
				rect.width = offsetX;
			}
			const auto direction = agentToDestination / distance;
			EMath::Vector2 velocity = direction * moveSpeed;
			position += velocity * GetFrameTime();
		}
		else {
			cd = 20;
			getTHING = 1;
			mState = state::Mining;
		}
		DrawText("Go to MINE", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	case state::Mining:
		cd-= GetFrameTime();
		getTHING -= GetFrameTime();
		if (getTHING <= 0) {
		mGold += rand()%5;
		mEnergy -= 5;
		mHunger -= 2;
		getTHING = 1;
		}

		if (cd <= 0) {
			getTHING = 1;
			mState = state::goSaloon;
		}
		DrawText("MINING", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	case state::goSaloon:
		agentToDestination = positionSaloon - position;
		distance = EMath::Magnitude(agentToDestination);
		if (distance > 10.0f)
		{
			currentTime += GetFrameTime();
			if (currentTime > animMaxTime) {
				currentFrame++;
				currentFrame = currentFrame % frame;
				rect.x = currentFrame * offsetX;
				currentTime = 0.0f;
				rect.width = offsetX;
			}
			const auto direction = agentToDestination / distance;
			EMath::Vector2 velocity = direction * moveSpeed;
			position += velocity * GetFrameTime();
		}
		else {
			cd = 5;
			mState = state::Drinking;
		}
		DrawText("Go to SALOON", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	case state::Drinking:
		cd -= GetFrameTime();
		getTHING -= GetFrameTime();
		if (getTHING <= 0) {
			mGold -= 5;
			getTHING = 1;
		}


		if (mGold <= 0 || cd <= 0) {
			mHunger = 100;
		mState = state::goHome;
		}
		DrawText("DRINKING", (int)position.x, (int)(position.y - 35.0f), 18, WHITE);
		break;
	}

	DrawTextureRec(myTexture, rect, { position.x,position.y }, WHITE);
	DrawText(std::to_string(mGold).c_str(), (int)position.x, (int)(position.y - 5.0f), 16, YELLOW);
	DrawText(std::to_string(mEnergy).c_str(), (int)(position.x + 50), (int)(position.y + 5), 16, DARKGREEN);
	DrawText(std::to_string(mHunger).c_str(), (int)(position.x + 50), (int)(position.y + 25), 16, ORANGE);
	DrawText(Name.c_str(), (int)(position.x), (int)(position.y+50), 16, mColor);
	if (cd > 0) {
	DrawText(std::to_string(cd).c_str(), (int)position.x, (int)(position.y - 20.0f), 16, mColor);
	}

	DrawText((Name+"'s House").c_str(), (int)positionHome.x, (int)positionHome.y +20, 16, mColor);
}