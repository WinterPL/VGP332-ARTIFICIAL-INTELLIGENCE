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
	mStateMachine->AddState<ZombieGohome>();
	mStateMachine->AddState<ZombieStayhome>();
	mStateMachine->ChangeState((int)State::Idle);

	std::string zombiePath = REng::ResourcesFullPath("ZombieAnim.png");
	mZombieSpritesheet = LoadTexture(zombiePath.c_str());
	std::string HomePath = REng::ResourcesFullPath("Bird.png");
	mHomeSprite = LoadTexture(HomePath.c_str());

	mTextureRect.x = 0.0f;
	mTextureRect.y = 0.0f;
	mTextureRect.width = static_cast<float>(mZombieSpritesheet.width) / static_cast<float>(mAnimFrames);
	const float numberOfAnimations = 2.0f;
	mTextureRect.height = static_cast<float>(mZombieSpritesheet.height) / numberOfAnimations;

	position = { 100.0f, 100.0f };
}

void Zombie::Unload()
{
	UnloadTexture(mZombieSpritesheet);
}

void Zombie::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Zombie::Render()
{
	float halfWidth = mTextureRect.width * 0.5f;
	float halfHeight = mTextureRect.height * 0.5f;

	DrawTexture(mHomeSprite,(int)(Home.x - 32),(int)(Home.y -32),WHITE);
	DrawText("Home", (int)(Home.x - 15.f) , (int)(Home.y - 40.f), 16, WHITE);
	DrawCircle((int)destination.x, (int)destination.y, 6.0f, GREEN);
	DrawCircle((int)Home.x, (int)Home.y, 6.0f, RED);
	DrawTextureRec(mZombieSpritesheet, mTextureRect, { position.x - halfWidth, position.y - halfHeight }, WHITE);
}


void Zombie::ChangeState(State state)
{
	mStateMachine->ChangeState((int)state);
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