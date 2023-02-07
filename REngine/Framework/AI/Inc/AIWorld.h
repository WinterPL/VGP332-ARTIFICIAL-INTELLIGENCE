#pragma once

namespace AI
{
	class Entity;
	using EntityPtrs = std::vector<Entity*>;
	class AIWorld {
	public:
		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		uint32_t GetNextID() {
			assert(mNextId < UINT32_MAX && "AIWorld - Run out of IDs");
		}

	private:
		EntityPtrs mEntities;
		uint32_t mNextId = 0;
	};
}