#pragma once

#include "PxRigidBody.h"
#include "PxShape.h"

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class mainGame; class ObjectSystem;

class RigidBody_Dynamic
{
public:
	RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float lifetime = -1, float density = 0.15, ObjectSystem* os = nullptr);
	~RigidBody_Dynamic();

	float getDensity() { return d; };
	float setDensity(float density) { d = density; };

	void addGen(ForceGenerator* force) { forces.push_back(force); };

	Vector3D getPos() { return Vector3D(tr.p.x, tr.p.y, tr.p.z); };

	bool canExpire() { return timeAlive >= lifetime; };

	virtual void integrate(double t);

protected:

	PxRigidDynamic* rigid;
	RenderItem* item;

	PxTransform tr;
	PxShape* s;
	mainGame* g;

	float d;
	float lifetime;
	ObjectSystem* os;

	float timeAlive;

	vector<ForceGenerator*> forces;
};