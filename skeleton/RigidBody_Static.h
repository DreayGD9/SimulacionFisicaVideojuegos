#pragma once

#include "PxRigidBody.h"
#include "PxShape.h"

#include <PxPhysicsAPI.h>
#include "Vector3D.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class mainGame;

class RigidBody_Static
{
public:
	RigidBody_Static(PxTransform transform, PxShape* shape, Vector4 colour, mainGame* game);
private:

	PxRigidStatic* rigid;
	RenderItem* item;

	PxTransform tr;
	PxShape* s;
	mainGame* g;
};

