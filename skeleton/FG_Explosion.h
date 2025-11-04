#pragma once

#include "ForceGenerator.h"
class FG_Explosion : public ForceGenerator
{
public:
	FG_Explosion(string n, float ePow, float eVexp, float eDelay, Vector3D areaPos = { 0,0,0 }, float areaRad = 1, float tConst = 1) :
		ForceGenerator(n, true, areaPos, areaRad), eP(ePow), eV(eVexp), boomDelay(eDelay), eR(0), tC(tConst), t(0), tSinceLastBoom(0) {
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {

		float dx = p.xV - aP.xV;
		float dy = p.yV - aP.yV;
		float dz = p.zV - aP.zV;
		float dist = sqrt(dx * dx + dy * dy + dz * dz);

		eR = eV * t;
		if (eR >= aR) eR = aR;
		
		if ((!aA || (aA && isWithinArea(p))) && dist < eR) {
			float powerF = eP / pow(dist, 2);
			float dT = -(t / tC);
			float timeF = powf(exp(1.0), dT);

			float rX = powerF * (dx) * timeF;
			float rY = powerF * (dy) * timeF;
			float rZ = powerF * (dz) * timeF;

			Vector3D result = { rX, rY, rZ };

			return result / m;
		}
		else return { 0,0,0 };
	};

	void emit() {
		cout << "boom" << endl;
		eR = 0;
		t = 0;
		tSinceLastBoom = 0;
	}

	void update(double time) {
		t += time;

		if (tSinceLastBoom >= boomDelay) {
			emit();
		}
		else tSinceLastBoom += time;
	}

private:
	float eP;
	float eV;
	float eR;
	float tC;
	float t;

	float tSinceLastBoom;
	float boomDelay;
};