#pragma once

namespace AI
{
	class AIWorld;
	using EntityPtrs = std::vector<Entity*>;
	class Entity {
	public:
		Entity(AIWorld& _world, uint32_t typeId);
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator = (const Entity&) = delete;
		Entity(Entity&) = delete;
		Entity& operator = (const Entity&&) = delete;

		AIWorld& world;
		float x = 0.0f, y = 0.0f;
		float headingX = 0.0f, headingY = 0.0f;
		float radius = 1.0f;

		uint32_t GetTypeID() const { return static_cast<uint32_t>(mUniqueID >> 32); }
		uint64_t GetUniqueID() const { return mUniqueID; }

	private:
		const uint64_t mUniqueID = 0;
	};
}