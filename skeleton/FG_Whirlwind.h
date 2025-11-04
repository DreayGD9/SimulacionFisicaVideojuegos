#pragma once

#include "ForceGenerator.h"
class FG_Whirlwind : public ForceGenerator
{
public:
	FG_Whirlwind(string n, float wPow, Vector3D areaPos = { 0,0,0 }, float areaRad = 1) :
		ForceGenerator(n, true, areaPos, areaRad), wP(wPow) {
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (!aA || (aA && isWithinArea(p))) {
			float sX = -(p.xV - aP.xV) * wP;
			float sY = 50 - ((p.yV - aP.yV) * wP);
			float sZ = -(p.zV - aP.zV) * wP;

			Vector3D result = { sX, sY, sZ };

			return result / m;
		}
		else return { 0,0,0 };
	};
private:
	float wP;
};