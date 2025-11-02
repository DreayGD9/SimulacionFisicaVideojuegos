#pragma once

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"
#include <list>

using namespace physx;
using namespace std;

class ParticleSystem;

class Particle
{
public:
	Particle(PxShape* s, Vector3D p, Vector3D v, float m, float l, ParticleSystem* ps);
	~Particle();

	void addForce(Vector3D f);

	void debug(bool e) { DEBUG = e; };

	bool canExpire() { return timeAlive >= lifetime; };

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D accel;
	float mass;
	float lifetime;
	ParticleSystem* partsys;

	float timeAlive;

	vector<Vector3D> forces;
	float damping = 0.01;

	bool DEBUG = false;

	physx::PxTransform tr;
	RenderItem* renderItem;
};

