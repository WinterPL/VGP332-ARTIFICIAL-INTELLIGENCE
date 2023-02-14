#include "Precompiled.h"
#include "Entity.h"

#include "AIWorld.h"

using namespace AI;

Entity::Entity(AIWorld& _world, uint32_t typeId)
	:world(_world)
	,mUniqueID(static_cast<uint64_t>(typeId) << 32 | _world.GetNextID())
	//63                     32 31                    0
	//[        typeID         ] [        nextID       ]
{
	world.RegisterEntity(this);
}

Entity::~Entity()
{
	world.UnregisterEntity(this);
}