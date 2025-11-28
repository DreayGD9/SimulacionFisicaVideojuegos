#pragma once

#include "PxRigidBody.h"
#include <vector>

class mainGame;
class ForceGenerator;
class Vector3D;
class Vector4;
class RenderItem;

using namespace physx;

class RigidBody_Dynamic
{
public:
	RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float density = 0.15);

	void addGen(ForceGenerator* force) { forces.push_back(force); };

	virtual void integrate(double t);

private:

	PxRigidDynamic* rigid;
	RenderItem* item;

	PxTransform tr;
	PxShape* s;
	mainGame* g;

	std::vector<ForceGenerator*> forces;
};