#pragma once

#include "RigidBody_Static.h"

class Floor : public RigidBody_Static
{
public:
	Floor(Vector3D pos, float width1, float width2, float height, Vector4 colour, mainGame* g) : 
		RigidBody_Static(
			PxTransform(pos.xV, pos.yV, pos.zV),
			CreateShape(PxBoxGeometry(width1, height, width2), g->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f)),
			colour,
			g) 
	{
		
	}
private:
};

