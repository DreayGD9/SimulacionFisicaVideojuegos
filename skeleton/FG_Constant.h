#pragma once

#include "ForceGenerator.h"

class FG_Constant : public ForceGenerator
{
public:
	FG_Constant(Vector3D f) {
		force = f;
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) { return force; };
private:
	Vector3D force;
};

