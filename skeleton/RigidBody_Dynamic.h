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
private:

	PxRigidDynamic* rigid;
	RenderItem* item;

	PxTransform tr;
	PxShape* s;
	mainGame* g;
};