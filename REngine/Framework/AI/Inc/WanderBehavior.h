#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	class WanderBehavior : public SteeringBehavior
	{
	public:
		EMath::Vector2 Calculate(Agent& agent)override;
		void Setup(float radius, float distance, float jitter);

	private:
		EMath::Vector2 mLocalWanderTarget = EMath::Vector2::YAxis();

		float mWanderRadius = 1.0f;
		float mWanderDistance = 0.0f;
		float mWanderJitter = 0.0f;
	};
}