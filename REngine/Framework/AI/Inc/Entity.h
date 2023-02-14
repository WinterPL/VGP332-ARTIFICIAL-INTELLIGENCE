#pragma once

namespace AI
{
	class AIWorld;
	class Entity
	{
	public:
		Entity(AIWorld& _world, uint32_t typeId);
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;

		AIWorld& world;
		EMath::Vector2 position = EMath::Vector2::Zero();
		EMath::Vector2 heading = EMath::Vector2::YAxis();
		float radius = 1.0f;

		uint32_t GetTypeID() const { return static_cast<uint32_t>(mUniqueID >> 32); }
		uint64_t GetUniqueID() const { return mUniqueID; }

	private:
		const uint64_t mUniqueID = 0;
	};
}

//What is the difference between * and &?
//AIWorld* world
//AIWorld& world

//Parameter passing
//1) Pass by value / Copy!
//2) Pass by reference
//3) Pass by pointer

//void Print(int i);

//void Swap(int* a, int* b)
//{
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//void Swap(int& a, int& b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}
//
//
//void Test()
//{
//	int i = 42;
//
//	int* iptr;
//	iptr = &i; //Assignment
//
//	int& iref = i; //Initialization
//}
//
//// You always read 'const' from right to left
//char* c;				//c is a pointer to a character
//const char* c;			//c is a pointer to character constant
//char* const c;			//c is a constant pointer to a character
//const char* const c;	//c is a constant pointer to a character constant
//const char& c;			//c is a reference to a character constant
//
////Conclusion: & ==== *const
//
//class Elephant
//{
//	char lotsofstuff[1000000];
//};
//
////void Print(Elephant e)
////void Print(Elephant& e)
////void Print(Elephant* e)
////void Print(const Elephant& e)
//
//int main()
//{
//	int x = 7;
//	int y = 14;
//	Swap(x, y);
//	return 0;
//}