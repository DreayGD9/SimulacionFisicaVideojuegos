#pragma once

#include "ForceGenerator.h"

class FG_Constant : public ForceGenerator
{
public:
	FG_Constant(string n, Vector3D f, bool massAffected, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 0) :
		ForceGenerator(n, areaAffected, areaPos, areaRad), force(f), mA(massAffected) {};

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (!aA || (aA && isWithinArea(p))) {
			if (mA) return force / m;
			else return force;
		}
		else return { 0,0,0 };
	}
private:
	Vector3D force;
	bool mA;
};

