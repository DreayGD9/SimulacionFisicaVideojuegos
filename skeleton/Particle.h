#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D p, Vector3D v, Vector3D a);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D accel;
	float damping = 0.01;
	physx::PxTransform* tr;
	RenderItem* renderItem;
};

