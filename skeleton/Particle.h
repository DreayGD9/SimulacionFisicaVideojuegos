#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Force.h"
#include <list>

using namespace std;

class Particle
{
public:
	Particle(Vector3D p, Vector3D v, float m);
	~Particle();

	void addForce(Force f);
	void delForce(string n);

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D accel;
	float mass;
	list<Force> forces;
	float damping = 0.01;

	const Force gravity = Force("GRAVITY", { 0, -9.8, 0 });

	physx::PxTransform tr;
	RenderItem* renderItem;
};

