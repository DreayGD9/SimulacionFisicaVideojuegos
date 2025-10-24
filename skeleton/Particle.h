#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"
#include <list>

using namespace std;

class Particle
{
public:
	Particle(Vector3D p, Vector3D v, float m);
	~Particle();

	void addGenerator(ForceGenerator* g);
	void remGenerator(ForceGenerator* g);

	void debug(bool e) { DEBUG = e; };

	void integrate(double t);
	Vector3D generateAccel();

private:
	Vector3D vel;
	Vector3D accel;
	float mass;

	list<ForceGenerator*> forceGens;

	float damping = 0.01;

	bool DEBUG = false;

	physx::PxTransform tr;
	RenderItem* renderItem;
};

