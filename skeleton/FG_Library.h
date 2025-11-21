#pragma once

#include "ForceGenerator.h"
#include "Particle.h"


// --------------------------
// CONSTANTE
// --------------------------

class FG_Constant : public ForceGenerator
{
public:
	FG_Constant(string n, Vector3D f, bool massAffected, bool a, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 0) :
		ForceGenerator(n, FG_CONSTANT, a, areaAffected, areaPos, areaRad), force(f), mA(massAffected) {
	};

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (active && (!aA || (aA && isWithinArea(p)))) {
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
	FG_Wind(string n, float wPow, Vector3D wSpe, bool a, bool areaAffected = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 1) :
		ForceGenerator(n, FG_WIND, a, areaAffected, areaPos, areaRad), wP(wPow), wS(wSpe.normalize()) {
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (active && (!aA || (aA && isWithinArea(p)))) {
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
	FG_Whirlwind(string n, float wPow, bool a, Vector3D areaPos = { 0,0,0 }, float areaRad = 1) :
		ForceGenerator(n, FG_WHIRLWIND, a, true, areaPos, areaRad), wP(wPow) {
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (active && (!aA || (aA && isWithinArea(p)))) {
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
	FG_Explosion(string n, float ePow, float eVexp, float eDelay, bool a, bool automatic = false, Vector3D areaPos = { 0,0,0 }, float areaRad = 1, float tConst = 1) :
		ForceGenerator(n, FG_EXPLOSION, a, true, areaPos, areaRad), eP(ePow), eV(eVexp), boomDelay(eDelay), aut(automatic), eR(0), tC(tConst), t(0), tSinceLastBoom(0) {
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {

		if (true) {
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
		}
		else return { 0,0,0 };
	};

	void explode() {
		setActive(true);
		eR = 0;
		t = 0;
		tSinceLastBoom = 0;
	}

	void update(double time) {
		t += time;

		if (tSinceLastBoom >= boomDelay) {
			setActive(false);
			if (aut) explode();
		}
		else tSinceLastBoom += time;
	}

	void setAuto(bool a) { aut = a; };
	void toggleAuto() { aut = !aut; };

private:
	bool aut;

	float eP;
	float eV;
	float eR;
	float tC;
	float t;

	float tSinceLastBoom;
	float boomDelay;
};

// --------------------------
// MUELLE
// --------------------------

class FG_Spring : public ForceGenerator
{
public:
	FG_Spring(string n, float elasticity, float restingLength, Particle* other, bool a, bool anchored = false, Vector3D anchorPos = {0,0,0}) :
		ForceGenerator(n, FG_SPRING, a, false, {0,0,0}, 0), k(elasticity), rL(restingLength), p2(other), a(anchored), aP(anchorPos) {
	};

	void setK(float elasticity) { k = elasticity; };

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (active) {
			Vector3D relativePos;
			if (a) relativePos = aP - p;
			else relativePos = p2->getPos() - p;

			float length = relativePos.magnitude();
			float deltaX = length - rL;
			Vector3D force = relativePos * deltaX * k;
			return force;
		}
		else return { 0,0,0 };
	};
private:
	float k;
	float rL;
	Particle* p2;
	bool a;
	Vector3D aP;
};

// --------------------------
// PLAYER SPEED
// --------------------------

class FG_PlrSpeed : public ForceGenerator
{
public:
	FG_PlrSpeed(string n, float s, float ms) :
		ForceGenerator(n, FG_PLRSPEED, true, false), str(s), currStr(0), maxStr(ms)  {
		forceVector = { 0,0,0 };
		holdingForward = false;
		holdingBackward = false;
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		if (active) return forceVector / m;
		else return { 0,0,0 };
	};

	void update(double t) {
		if (active) {
			if (holdingForward) {
				currStr += str * t;
				if (currStr >= maxStr) currStr = maxStr;
			}
			else if (holdingBackward) {
				currStr -= str * t;
				if (currStr <= -maxStr) currStr = -maxStr;
			}
			else {
				if (currStr > 0.1) currStr -= str * t;
				else if (currStr < -0.1) currStr += str * t;
				else currStr = 0;
			}
			forceVector = { currStr, 0, 0 };
		}
	}

	void forward() {
		holdingForward = true;
		holdingBackward = false;
	}

	void backward() {
		holdingForward = false;
		holdingBackward = true;
	}

	void stop() {
		holdingForward = false;
		holdingBackward = false;
	}

private:
	float str;
	float currStr;
	float maxStr;
	Vector3D forceVector;
	bool holdingForward;
	bool holdingBackward;
};