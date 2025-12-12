#pragma once

#include "RigidBody_Dynamic.h"
#include "ForceGenerator.h"
#include <list>

class mainGame;

class Player : public RigidBody_Dynamic
{
public:
	Player(PxTransform tr, float m, float ms, PxShape* s, Vector4 c, mainGame* g);
	~Player();

	void update(float t);
	void integrate(float t);
	void addGen(ForceGenerator* force);
private:

	float maxSpd;
	bool horizontallyLocked;

	list<ForceGenerator*> forces;
	mainGame* game;

	bool lockY;
	bool lockZ;
};

