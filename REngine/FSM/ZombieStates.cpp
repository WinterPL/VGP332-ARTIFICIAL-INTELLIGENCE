#include "ZombieStates.h"
#include "Brain.h"
#include "TypeId.h"

namespace
{
	EMath::Vector2 offsetDebugText = { 50.0f, -80.0f };
}

/// <summary>
/// Zombie Idle State
/// </summary>
/// <param name="agent"></param>
void ZombieIdle::Enter(Zombie& agent)
{
	mWaitTime = 1.0f;
	agent.UpdateHunger();
}

void ZombieIdle::Update(Zombie& agent, float deltaTime)
{
	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if (agent.IsHungry())
		{
			agent.ChangeState(Zombie::State::Eat);
		}
		else
		{
			agent.ChangeState(Zombie::State::Wander);
		}
	}
	EMath::Vector2 textPosition = agent.position + offsetDebugText;
	DrawText(agent.IsHungry() ? "Hungry" : "Not Hungry", (int)textPosition.x, (int)(textPosition.y - 40.0f), 16, agent.IsHungry() ? YELLOW : WHITE);
	DrawText(std::to_string(mWaitTime).c_str(), (int)textPosition.x, (int)(textPosition.y - 20.0f), 16, WHITE);
	DrawText(std::to_string(agent.numE).c_str(), (int)textPosition.x, (int)(textPosition.y + 20.f), 16, WHITE);
	DrawText("Idle", (int)textPosition.x, (int)textPosition.y, 16, WHITE);
}

void ZombieIdle::Exit(Zombie& agent)
{
	
}


/// <summary>
/// Zombie Wander State
/// </summary>
/// <param name="agent"></param>
void ZombieWander::Enter(Zombie& agent)
{
	float randomX = EMath::RandomFloat(100.0f, 1500.0f);
	float randomY = EMath::RandomFloat(100.0f, 800.0f);
	agent.destination.x = randomX;
	agent.destination.y = randomY;
}

void ZombieWander::Update(Zombie& agent, float deltaTime)
{
	const auto agentToDestination = agent.destination - agent.position;
	const float distance = EMath::Magnitude(agentToDestination);

	if (distance > 10.0f)
	{
		const auto direction = agentToDestination / distance;
		agent.velocity = direction * 300.0f;
		agent.position += agent.velocity * deltaTime;

		agent.UpdateAnimation(deltaTime);
	}
	else
	{
		agent.ChangeState(Zombie::State::Idle);
	}

	EMath::Vector2 textPosition = agent.position + offsetDebugText;
	DrawText("Wander", (int)textPosition.x, (int)textPosition.y, 16, WHITE);
}

void ZombieWander::Exit(Zombie& agent)
{

}


/// <summary>
/// Zombie Eat State
/// </summary>
/// <param name="agent"></param>
void ZombieEat::Enter(Zombie& agent)
{
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::BrainID);
	float minDistance = FLT_MAX;
	for (auto entity : entities)
	{
		float distanceSqr = EMath::MagnitudeSqr(agent.position - entity->position);
		if (distanceSqr < minDistance)
		{
			minDistance = distanceSqr;
			mTarget = static_cast<Brain*>(entity);
		}
	}
}

void ZombieEat::Update(Zombie& agent, float deltaTime)
{
	if (mTarget)
	{
		const auto agentToTarget = mTarget->position - agent.position;
		const float distance = EMath::Magnitude(agentToTarget);

		if (distance > 5.0f)
		{
			const auto direction = agentToTarget / distance;
			agent.velocity = direction * 500.0f;
			agent.position += agent.velocity * deltaTime;

			agent.UpdateAnimation(deltaTime);
		}
		else
		{
			agent.EatBrain();
			mTarget->Consume();
			
			if (agent.numE > 0) {
			agent.ChangeState(Zombie::State::Idle);
			}
			else{
				std::cout << "Gohome" << std::endl;
				agent.ChangeState(Zombie::State::Gohome);
			}
			
		}
	}
	EMath::Vector2 textPosition = agent.position + offsetDebugText;
	DrawText(std::to_string(agent.numE).c_str(), (int)textPosition.x, (int)(textPosition.y), 16, WHITE);
}

void ZombieEat::Exit(Zombie& agent)
{

}


void  ZombieGohome::Enter(Zombie& agent)
{
	agent.destination.x = agent.Home.x;
	agent.destination.y = agent.Home.y;
}

void ZombieGohome::Update(Zombie& agent, float deltaTime)
{
	const auto agentToDestination = agent.destination - agent.position;
	const float distance = EMath::Magnitude(agentToDestination);

	if (distance > 10.0f)
	{
		const auto direction = agentToDestination / distance;
		agent.velocity = direction * 100.0f;
		agent.position += agent.velocity * deltaTime;

		agent.UpdateAnimation(deltaTime);
	}
	else
	{
		agent.ChangeState(Zombie::State::StayHome);
	}

	EMath::Vector2 textPosition = agent.position + offsetDebugText;
	DrawText("Go home", (int)textPosition.x, (int)textPosition.y, 16, WHITE);
}

void  ZombieGohome::Exit(Zombie& agent)
{

}


void  ZombieStayhome::Enter(Zombie& agent)
{
	mWaitTime = 5.0f;
	agent.UpdateHunger();
	agent.numE = 3;
}

void ZombieStayhome::Update(Zombie& agent, float deltaTime)
{
	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if (agent.IsHungry())
		{
			agent.ChangeState(Zombie::State::Eat);
		}
		else
		{
			agent.ChangeState(Zombie::State::Wander);
		}
	}
	EMath::Vector2 textPosition = agent.position + offsetDebugText;
	DrawText(agent.IsHungry() ? "Hungry" : "Not Hungry", (int)textPosition.x, (int)(textPosition.y - 40.0f), 16, agent.IsHungry() ? YELLOW : WHITE);
	DrawText(std::to_string(mWaitTime).c_str(), (int)textPosition.x, (int)(textPosition.y - 20.0f), 16, WHITE);
	DrawText(std::to_string(agent.numE).c_str(), (int)textPosition.x, (int)(textPosition.y + 20.f), 16, WHITE);
	DrawText("Rest", (int)textPosition.x, (int)textPosition.y, 16, WHITE);
	
}

void  ZombieStayhome::Exit(Zombie& agent)
{

}