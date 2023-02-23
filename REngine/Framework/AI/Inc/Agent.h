#pragma once

#include "Entity.h"

namespace AI
{
	class Agent;
	using AgentPtrs = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeID);
		~Agent() override = default;

		void SetAgentTarget(Agent* _target);

		EMath::Vector2 velocity = EMath::Vector2::Zero();
		EMath::Vector2 destination = EMath::Vector2::Zero();
		Agent* agentTarget;

		float maxSpeed = 100.0f;
		float mass = 1.0f;
	};
}