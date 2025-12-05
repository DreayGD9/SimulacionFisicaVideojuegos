#pragma once

#include "PxRigidBody.h"
#include "PxShape.h"
#include "mainGame.h"

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

