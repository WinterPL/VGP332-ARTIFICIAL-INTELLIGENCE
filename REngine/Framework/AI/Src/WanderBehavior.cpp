#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;

void WanderBehavior::Setup(float radius, float distance, float jitter) 
{
	mWanderDistance = distance;
	mWanderRadius = radius;
	mWanderJitter = jitter;
}

EMath::Vector2 WanderBehavior::Calculate(Agent& agent) 
{
	auto newWanderTarget = mLocalWanderTarget + (EMath::RandomUnitCircle() * mWanderJitter);
	
	newWanderTarget = EMath::Normalize(newWanderTarget) * mWanderRadius;

	newWanderTarget += EMath::Vector2(0.0f, mWanderDistance);

	const auto worldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = EMath::TransformNormal(newWanderTarget,worldTransform);

	const auto agentToDestination =worldWanderTarget - agent.position;
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
		DrawCircleLines(wanderCenter.x, wanderCenter.y, mWanderRadius,GREEN);
		DrawCircle(worldWanderTarget.x, worldWanderTarget.y, 5.0f, ORANGE);
		DrawLine(agent.position.x, agent.position.y, worldWanderTarget.x, worldWanderTarget.y, YELLOW);
	}


	return wanderForce;
}