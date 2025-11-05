#pragma once

#include "Particle.h"
#include "ForceGenerator.h"

class Player : public Particle
{
public:
	Player(Vector3D p, float m, float ms, PxShape* s, Vector4 c);
	~Player();

	void update(float t);
	void integrate(float t);
	void addGen(ForceGenerator* force);

	Vector3D returnPos();
private:
	Vector3D getAccel();

	float maxSpd;
	bool horizontallyLocked;

	list<ForceGenerator*> forces;
};

