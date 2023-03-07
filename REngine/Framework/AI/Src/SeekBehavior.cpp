#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace AI;

EMath::Vector2 SeekBehavior::Calculate(Agent& agent)
{
	const auto agentToDestination = agent.destination - agent.position;
	const float distToDestination = EMath::Magnitude(agentToDestination);

	if (distToDestination <= 0.0f)
	{
		return{};
	}

	const auto desiredVelocity = (agentToDestination / distToDestination) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		DrawLine((int)agent.position.x, (int)agent.position.y, (int)agent.position.x + (int)desiredVelocity.x, (int)agent.position.y + (int)desiredVelocity.y, YELLOW);
		DrawLine((int)agent.position.x, (int)agent.position.y, (int)agent.position.x + (int)agent.velocity.x, (int)agent.position.y + (int)agent.velocity.y, GREEN);
	}


	return seekForce;
}