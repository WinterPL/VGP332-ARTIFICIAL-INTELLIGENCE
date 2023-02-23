#include "Precompiled.h"
#include "SteeringModule.h"

using namespace AI;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

EMath::Vector2 SteeringModule::Calculate()
{
	EMath::Vector2 totalForce;

	for (auto& behavior : mBehaviors)
	{
		if (behavior->IsActive())
		{
			totalForce += behavior->Calculate(mAgent);
		}
	}

	return totalForce;
}