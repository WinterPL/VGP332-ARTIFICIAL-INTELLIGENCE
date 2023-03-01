#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;


void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}

EMath::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	//Apply random jitter to wander target
	auto newWanderTarget = mLocalWanderTarget + (EMath::RandomUnitCircle() * mWanderJitter);

	// This point is not in the circle anymore so we need to normalize it
	// Snap the new position back onto wander circle
	newWanderTarget = EMath::Normalize(newWanderTarget) * mWanderRadius;
	mLocalWanderTarget = newWanderTarget;

	//Project new position forward in front of the agent
	newWanderTarget += EMath::Vector2(0.0f, mWanderDistance);

	//Transform target into world space
	const auto worldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = EMath::TransformCoord(newWanderTarget, worldTransform);


	//Just seek
	const auto agentToDestination = worldWanderTarget - agent.position;
	const float distToDestination = EMath::Magnitude(agentToDestination);

	if (distToDestination <= 0.0f)
	{
		return{};
	}

	const auto desiredVelocity = (agentToDestination / distToDestination) * agent.maxSpeed;
	const auto wanderForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		const auto wanderCenter = EMath::TransformCoord({ 0.0f, mWanderDistance }, worldTransform);

		DrawCircleLines(wanderCenter.x, wanderCenter.y, mWanderRadius, GREEN);

		DrawCircle(worldWanderTarget.x, worldWanderTarget.y, 5.0f, ORANGE);
		DrawLine(agent.position.x, agent.position.y, worldWanderTarget.x, worldWanderTarget.y, YELLOW);
	}


	return wanderForce;
}