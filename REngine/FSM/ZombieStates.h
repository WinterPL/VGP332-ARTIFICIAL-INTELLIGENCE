#pragma once
#include "Zombie.h"
#include "Brain.h"

//Idle state
class ZombieIdle : public AI::State<Zombie>
{
public:
	void Enter(Zombie& agent) override;
	void Update(Zombie& agent, float deltaTime) override;
	void Exit(Zombie& agent) override;

private:
	float mWaitTime = 0.0f;
};

class ZombieWander : public AI::State<Zombie>
{
public:
	void Enter(Zombie& agent) override;
	void Update(Zombie& agent, float deltaTime) override;
	void Exit(Zombie& agent) override;
};

class Brain;
class ZombieEat : public AI::State<Zombie>
{
public:
	void Enter(Zombie& agent) override;
	void Update(Zombie& agent, float deltaTime) override;
	void Exit(Zombie& agent) override;

private:
	Brain* mTarget;
};