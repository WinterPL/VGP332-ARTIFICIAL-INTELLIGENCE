#include "Precompiled.h"
#include "AIWorld.h"

using namespace AI;
void AIWorld::RegisterEntity(Entity* entity) {
	assert(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end() && "AIWorld - Entity already registered");
	mEntities.push_back(entity);
}
void AIWorld::UnregisterEntity(Entity* entity) {
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end()) {
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
		//mEntities.erase(iter);
	}
}