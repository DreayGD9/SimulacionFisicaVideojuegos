#pragma once

#include <PxPhysicsAPI.h>
#include <iostream>
#include "RenderUtils.hpp"
#include "Vector3D.h"

using namespace std;
using namespace physx;

enum FG_TYPE
{
	FG_CONSTANT,
	FG_WIND,
	FG_WHIRLWIND,
	FG_EXPLOSION
};

enum FG_DEBUG_ACTIVE {
	FG_DEBUG_ACTIVE,
	FG_DEBUG_INACTIVE,
	FG_DEBUG_HIDDEN
};

class ForceGenerator
{
public:
	ForceGenerator(string n, FG_TYPE t, bool active, bool areaAffected = false, Vector3D areaPos = {0,0,0}, float areaRad = 1);

	string getName() { return name; };
	FG_TYPE getType() { return type; };
	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) { return Vector3D(0,0,0); };
	virtual void update(double t) {};

	bool isWithinArea(Vector3D pos);

	void setActive(bool a) ;
	void toggleActive();

	void updateDebugView();

protected:
	string name;
	FG_TYPE type;
	bool aA;
	Vector3D aP;
	float aR;

	bool active;

	RenderItem* debugView;
};

