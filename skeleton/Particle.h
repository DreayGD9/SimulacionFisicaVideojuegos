#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
};

