#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class ArriveBehavior : public SteeringBehavior
	{
	public:
		EMath::Vector2 Calculate(Agent& agent) override;
		void Setup(float radius, float distance, float jitter);

	private:
		EMath::Vector2 mLocalWanderTarget = EMath::Vector2::YAxis();

		float mGroupRadius = 5.0f;
		float mGroupDistance = 10.0f;
	};
}
