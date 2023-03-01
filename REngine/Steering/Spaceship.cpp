#include "Spaceship.h"
#include "TypeIds.h"

extern float wanderRadius;
extern float wanderDistance;
extern float wanderJitter;

Spaceship::Spaceship(AI::AIWorld& world)
	: Agent(world, Types::Spaceship)
{}

void Spaceship::Load()
{
	maxSpeed = 300.0f;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
	//mSeekBehavior->SetActive(false);
	mWanderBehavior->SetActive(true);


	//mSeekBehavior->ShowDebug(true);
	mWanderBehavior->ShowDebug(true);


	for (int i = 0; i < mTextures.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "SpaceshipSprites\\spaceship_%02i.png", i + 1);
		std::string textureName(name);
		std::string fullPath = REng::ResourcesFullPath(textureName);
		mTextures[i] = LoadTexture(fullPath.c_str());
	}
}

void Spaceship::Unload()
{}

void Spaceship::Update(float deltaTime)
{
	if (mWanderBehavior->IsActive())
	{
		mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
	}

	const auto force = mSteeringModule->Calculate();
	const auto acceleration = force / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

	//Truncate speed to not exceed maxSpeed
	if (EMath::MagnitudeSqr(velocity) > EMath::Sqr(maxSpeed))
	{
		velocity = EMath::Normalize(velocity) * maxSpeed;
	}

	//Screen wrapping
	const auto screenWidth = GetScreenWidth();
	const auto screenHeight = GetScreenHeight();

	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x >= screenWidth)
		position.x -= screenWidth;
	if (position.y < 0.0f)
		position.y += screenHeight;
	if (position.y >= screenHeight)
		position.y -= screenHeight;

	//Update heading vector if you have movement
	if (EMath::MagnitudeSqr(velocity) >= 1.0f)
	{
		heading = EMath::Normalize(velocity);
	}
}

void Spaceship::Render()
{
	float angle = atan2(-heading.x, heading.y) + EMath::kPi;
	float percent = angle / EMath::kTwoPi;

	const int frame = static_cast<int>(percent * mTextures.size()) % mTextures.size();

	DrawTexture(mTextures[frame], position.x - mTextures[frame].width * 0.5f, position.y - mTextures[frame].height * 0.5f, WHITE);
	DrawCircle(destination.x, destination.y, 5.0f, RED);
}