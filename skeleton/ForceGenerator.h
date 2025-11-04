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
	ForceGenerator(string n, bool areaAffected, Vector3D areaPos, float areaRad) : name(n), aA(areaAffected), aP(areaPos), aR(areaRad) {
		if (debug && areaAffected && aR > 0) {
			PxShape* s = CreateShape(PxSphereGeometry(aR));
			PxTransform* sTR = new PxTransform({ aP.xV, aP.yV, aP.zV });
			RenderItem* AxisSphereC = new RenderItem(s, sTR, { 1,1,1,0.5 });
		}
	};

	string getName() { return name; };
	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) { return Vector3D(0,0,0); };
	virtual void update(double t) {};

	bool isWithinArea(Vector3D pos) {
		if (aA && aR > 0) {
			float dx = pos.xV - aP.xV;
			float dy = pos.yV - aP.yV;
			float dz = pos.zV - aP.zV;

			float dist = sqrt(dx * dx + dy * dy + dz * dz);

			return (dist <= aR);
		}
		else return false;
	}

protected:
	string name;
	bool aA;
	Vector3D aP;
	float aR;

	bool debug = true;
};

