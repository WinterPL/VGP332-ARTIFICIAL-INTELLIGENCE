#pragma once

#include <AI.h>
#include <REngine.h>

class Zombie : public AI::Agent
{
public:
	enum State
	{
		Idle,
		Wander,
		Eat
	};

	Zombie(AI::AIWorld& world);
	void Load();
	void Unload();

	void ChangeState(State state);

	void Update(float deltaTime);
	void Render();
	void UpdateAnimation(float deltaTime);

	void EatBrain() { mHunger = 0.0f; }
	bool IsHungry() { return mHunger >= 100.0f; }
	void UpdateHunger() { mHunger += EMath::RandomFloat(50.0f, 90.0f); }

private:
	std::unique_ptr<AI::StateMachine<Zombie>> mStateMachine;

	Texture2D mZombieSpritesheet;
	Rectangle mTextureRect;

	float mHunger = 0.0f;

	//Zombie animation
	int mCurrentFrame = 0;
	float mCurrentTime = 0.0f;
	const int mAnimFrames = 4;
	const float mFrameDuration = 0.3f;

};