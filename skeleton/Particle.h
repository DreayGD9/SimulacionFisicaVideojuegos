#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
public:
	Particle(Vector3D p, Vector3D v, Vector3D a);
	~Particle();

	void addForce(Vector3D f);
	void delForce(Vector3D f);

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D accel;
	//list<Vector3D> forces;
	float damping = 0.01;
	physx::PxTransform tr;
	RenderItem* renderItem;
};

