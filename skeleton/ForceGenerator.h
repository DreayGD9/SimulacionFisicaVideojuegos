#pragma once

#include "Vector3D.h"

class ForceGenerator
{
public:
	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) { return Vector3D(0,0,0); };
};

