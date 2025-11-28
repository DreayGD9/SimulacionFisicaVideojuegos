#pragma once

#include "RigidBody_Static.h"

class Floor : public RigidBody_Static
{
public:
	Floor(PxTransform transform, float width1, float width2, float height, Vector4 colour, mainGame* g) : 
		RigidBody_Static(
			transform, 
			CreateShape(PxBoxGeometry(width1, height, width2)), 
			colour,
			g) 
	{
		
	}
private:
};

