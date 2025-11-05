#pragma once

#include "ParticleSystem.h"

class Player;

class Enemy : public Particle
{
public:
	Enemy(Vector3D p, float m, float ms, PxShape* s, Vector4 c, float d, Player* pl);
	~Enemy();

	void update(float t);
	void integrate(float t);
	void addGen(ForceGenerator* force);

	void fire();

	ParticleSystem* getLauncherPS();

private:
	Vector3D getAccel();

	float maxSpd;
	bool horizontallyLocked;
	float shotDelay;

	ParticleSystem* launcher;
	list<ForceGenerator*> forces;

	Player* player;
};
