#include "Brain.h"
#include "TypeId.h"

Brain::Brain(AI::AIWorld& world)
	:Entity(world, Types::BrainID)
{}

void Brain::Load()
{
	std::string brainFullPath = REng::ResourcesFullPath("brain.png");
	mTexture = LoadTexture(brainFullPath.c_str());
}

void Brain::Unload()
{
}

void Brain::Update(float deltaTime)
{}

void Brain::Render()
{
	DrawTexture(mTexture, position.x - mTexture.width * 0.5f, position.y - mTexture.height * 0.5f, WHITE);
}