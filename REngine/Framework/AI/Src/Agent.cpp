#include "Precompiled.h"
#include "Agent.h"

using namespace AI;
Agent::Agent(AIWorld& world, uint32_t typeID)
	: Entity(world, typeID)
{}

void Agent::SetAgentTarget(Agent* _target)
{
	agentTarget = _target;
}