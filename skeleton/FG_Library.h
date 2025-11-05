#pragma once

#include "ForceGenerator.h"

// --------------------------
// CONSTANTE
// --------------------------

class FG_Constant : public ForceGenerator
{
public:
	FG_Constant(string n, Vector3D f, bool massAffected, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 0) :
		ForceGenerator(n, areaAffected, areaPos, areaRad), force(f), mA(massAffected) {
	};

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

// --------------------------
// VIENTO
// --------------------------

class FG_Wind : public ForceGenerator
{
public:
	FG_Wind(string n, float wPow, Vector3D wSpe, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 1) :
		ForceGenerator(n, areaAffected, areaPos, areaRad), wP(wPow), wS(wSpe.normalize()) {
	}

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

// --------------------------
// TORBELLINO
// --------------------------

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

// --------------------------
// EXPLOSION
// --------------------------

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

			float rX = powerF * (dx)*timeF;
			float rY = powerF * (dy)*timeF;
			float rZ = powerF * (dz)*timeF;

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