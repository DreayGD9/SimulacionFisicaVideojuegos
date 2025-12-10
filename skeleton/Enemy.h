#pragma once

#include "ObjectSystem.h"
#include "ParticleSystem.h"

class Player; class mainGame;

class Enemy : public Particle
{
public:
	Enemy(Vector3D p, float m, float ms, PxShape* s, Vector4 c, float d, float pow, Player* pl, mainGame* g);
	~Enemy();

	void update(float t);
	void integrate(float t);
	void addGen(ForceGenerator* force);
	void addGenToShots(ForceGenerator* force);

	void fire();

	ParticleSystem* getLauncherPS();

private:
	Vector3D getAccel();

	float maxSpd;
	bool horizontallyLocked;
	float shotDelay;
	float shotPower;

	ObjectSystem* launcher;
	list<ForceGenerator*> forces;

	Player* player;
	mainGame* game;
};
