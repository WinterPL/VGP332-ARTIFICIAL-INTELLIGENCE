#include "Precompiled.h"
#include "GroupBehavior.h"

#include "Agent.h"

using namespace AI;


void GroupBehavior::Setup(float radius, float distance, float jitter)
{
	mGroupRadius = radius;
	mGroupDistance = distance;

}

EMath::Vector2 GroupBehavior::Calculate(Agent& agent)
{
	return {};
}