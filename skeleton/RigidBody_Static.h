#pragma once

#include "PxRigidBody.h"

class MainGame;
class Vector4;

using namespace physx;

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

