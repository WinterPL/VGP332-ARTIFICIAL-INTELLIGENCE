#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace AI;

void ArriveBehavior::Setup(float radius, float distance, float jitter)
{
	mGroupRadius = radius;
	mGroupDistance = distance;

}

EMath::Vector2 ArriveBehavior::Calculate(Agent& agent)
{
	const auto agentToDestination = agent.destination - agent.position;
	const float distToDestination = EMath::Magnitude(agentToDestination);

	if (distToDestination <= 0.0f)
	{
		return{};
	}

	const auto desiredVelocity = (agentToDestination / distToDestination) * agent.maxSpeed;
	const auto seekForce = -desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		DrawLine((int)agent.position.x, (int)agent.position.y, (int)agent.position.x + desiredVelocity.x, (int)agent.position.y + desiredVelocity.y, YELLOW);
		DrawLine((int)agent.position.x, (int)agent.position.y, (int)agent.position.x + agent.velocity.x, (int)agent.position.y + agent.velocity.y, GREEN);
	}


	return seekForce;
}