#include "SteeringBehavior.h"

namespace AI
{
	class SeekBehavior : public SteeringBehavior
	{
	public:
		EMath::Vector2 Calculate(Agent& agent) override;
	};
}