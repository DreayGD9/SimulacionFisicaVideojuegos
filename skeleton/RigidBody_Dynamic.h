#pragma once

#include "PxRigidBody.h"
#include "PxShape.h"

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class mainGame;

class RigidBody_Dynamic
{
public:
	RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float density = 0.15);

	float getDensity() { return d; };
	float setDensity(float density) { d = density; };

	void addGen(ForceGenerator* force) { forces.push_back(force); };

	Vector3D getPos() { return Vector3D(tr.p.x, tr.p.y, tr.p.z); };

	bool canExpire() { return timeAlive >= lifetime; };

	virtual void integrate(double t);

private:

	PxRigidDynamic* rigid;
	RenderItem* item;

	PxTransform tr;
	PxShape* s;
	mainGame* g;

	float d; 
	float lifetime;
	//ParticleSystem* partsys;

	float timeAlive;

	vector<ForceGenerator*> forces;
};