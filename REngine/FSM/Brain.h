#pragma once

#include <AI.h>
#include <REngine.h>

class Brain : public AI::Entity
{
public:
	Brain(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	bool IsConsumed() const { return mConsumed; }
	void Consume() { mConsumed = true; }

private:
	bool mConsumed = false;
	Texture2D mTexture;
};