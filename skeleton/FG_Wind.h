#pragma once

#include "ForceGenerator.h"
class FG_Wind : public ForceGenerator
{
public:
	FG_Wind(string n, float wPow, Vector3D wSpe, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 0) : 
		ForceGenerator(n, areaAffected, areaPos, areaRad), wP(wPow), wS(wSpe.normalize()) {}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (!aA || (aA && isWithinArea(p))) {
			return ((wS * wP) - v) / m;
		}
		else return { 0,0,0 };
	};
private:
	float wP;
	Vector3D wS;
};

