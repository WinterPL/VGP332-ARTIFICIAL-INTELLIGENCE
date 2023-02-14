#include "Precompiled.h"
#include "AIWorld.h"

#include "Entity.h"

using namespace AI;

void AIWorld::RegisterEntity(Entity* entity)
{
	assert(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end() &&
		"AIWorld - Entity already registered.");
	mEntities.push_back(entity);
}

void AIWorld::UnregisterEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1); //Constant time removal
		mEntities.pop_back();
	}
}

std::vector<Entity*> AIWorld::GetAllEntitiesOfType(uint32_t typeID)
{
	std::vector<Entity*> entities;
	for (auto entity : mEntities)
	{
		if (entity->GetTypeID() == typeID)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}