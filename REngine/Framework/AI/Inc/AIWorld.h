#pragma once

namespace AI
{
	class Entity;
	using EntityPtrs = std::vector<Entity*>;

	class AIWorld
	{
	public:
		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		std::vector<Entity*> GetAllEntitiesOfType(uint32_t typeID);

		uint32_t GetNextID() const
		{
			assert(mNextId < UINT32_MAX && "AIWorld - Run out of IDs");
			return mNextId++;
		}

	private:
		EntityPtrs mEntities;
		mutable uint32_t mNextId = 0;
	};
}


//class Phonebook
//{
//public:
//	struct Info
//	{
//		std::string name;
//		....
//	};
//
//	auto Reset() const { mCurrentIndex = 0; }
//	auto Next() const { mCurrentIndex++; }
//	const Info& GetNext() const { return mDatabase[mCurrentIndex]; }
//
//private:
//	std::vector<Info> mDatabase;
//	mutable int mCurrentIndex;
//
//};
//
//void PrintAllContact(const Phonebook& ph)
//{
//	pb.Reset();
//	while (true)
//	{
//		pg.GetNext();
//	}
//}

//What is the difference between C cast and C++ cast?
//static_cast - compile
//dynamic_cast - Run time
//Reinterpret_cast
//const_cast


