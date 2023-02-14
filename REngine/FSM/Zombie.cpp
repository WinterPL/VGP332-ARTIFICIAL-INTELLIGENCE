#include "Zombie.h"
#include "ZombieStates.h"

#include "TypeId.h"

Zombie::Zombie(AI::AIWorld& world)
	: Agent(world, Types::ZombieID)
{}

void Zombie::Load()
{
	//Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Zombie>>(*this);
	mStateMachine->AddState<ZombieIdle>();
	mStateMachine->AddState<ZombieWander>();
	mStateMachine->AddState<ZombieEat>();
	mStateMachine->ChangeState(Idle);

	std::string zombiePath = REng::ResourcesFullPath("ZombieAnim.png");
	Texture2D zombie = LoadTexture(zombiePath.c_str());
	mZombieSpritesheet = zombie;

	mTextureRect.x = 0.0f;
	mTextureRect.y = 0.0f;
	mTextureRect.width = static_cast<float>(mZombieSpritesheet.width) / static_cast<float>(mAnimFrames);
	const float numberOfAnimations = 2.0f;
	mTextureRect.height = static_cast<float>(mZombieSpritesheet.height) / numberOfAnimations;

	position = { 100.0f, 100.0f };
}

void Zombie::Unload()
{

}

void Zombie::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Zombie::Render()
{
	float halfWidth = mTextureRect.width * 0.5f;
	float halfHeight = mTextureRect.height * 0.5f;

	DrawTextureRec(mZombieSpritesheet, mTextureRect, { position.x - halfWidth, position.y - halfHeight }, WHITE);
	DrawCircle(destination.x, destination.y, 6.0f, GREEN);
}


void Zombie::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}

void Zombie::UpdateAnimation(float deltaTime)
{
	mCurrentTime += deltaTime;
	if (mCurrentTime > mFrameDuration)
	{
		mCurrentFrame += 1;
		mCurrentFrame %= mAnimFrames;
		mCurrentTime = 0.0f;
	}

	mTextureRect.x = static_cast<float>(mCurrentFrame) * static_cast<float>(mZombieSpritesheet.width) / static_cast<float>(mAnimFrames);
}