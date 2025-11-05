#pragma once

#include <PxPhysicsAPI.h>
#include <iostream>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using namespace std;
using namespace physx;


class ForceGenerator
{
public:
	ForceGenerator(string n, bool areaAffected, Vector3D areaPos = {0,0,0}, float areaRad = 1);

	string getName() { return name; };
	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) { return Vector3D(0,0,0); };
	virtual void update(double t) {};

	bool isWithinArea(Vector3D pos);

protected:
	string name;
	bool aA;
	Vector3D aP;
	float aR;

	bool debug = true;
};

