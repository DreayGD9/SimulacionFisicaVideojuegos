#pragma once

#include "Vector3D.h"

class ForceGenerator
{
public:
	string getName() { return name; };
	virtual Vector3D getForce() { return force; };

protected:
	string name;
	Vector3D force;
};

