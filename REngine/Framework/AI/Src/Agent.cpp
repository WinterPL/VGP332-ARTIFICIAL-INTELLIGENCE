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

EMath::Matrix3 Agent::GetWorldTransform() const {
	const auto h = heading;
	const auto s = EMath::PerpendicularRH(h);
	const auto d = position;
	
	return { s.x,s.y,0.0f,
			 h.x,h.y,0.0f,
			 d.x,d.y,1.0f };
}