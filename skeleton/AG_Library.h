#pragma once

#include "AestheticGenerator.h"

// --------------------------
// TORNADO
// --------------------------

class AG_Tornado : public AestheticGenerator
{
public:
	AG_Tornado(string n, Vector3D pos, bool a) : AestheticGenerator(pos), centerPos(pos) {

		r = 40;

		string nameFG = n + "_FG_Whirlwind";
		FG_Whirlwind* whirlwind = new FG_Whirlwind(nameFG, 2000, a, centerPos, r, false);
		force = whirlwind;

		float rFactorPos = 0.75f;

		offsetP1 = { r * rFactorPos, 0, 0 };
		offsetP2 = { 0, 0, r * rFactorPos };
		offsetP3 = { -r * rFactorPos, 0, 0 };
		offsetP4 = { 0, 0, -r * rFactorPos };

		vector<Vector3D> posPs;
		Vector3D posVert = { 0, -r * 0.5f, 0 };
		posPs.push_back(offsetP1 + centerPos + posVert);
		posPs.push_back(offsetP2 + centerPos + posVert);
		posPs.push_back(offsetP3 + centerPos + posVert);
		posPs.push_back(offsetP4 + centerPos + posVert);

		vector<Vector3D> dirPs;
		Vector3D dirVert = { 0, r/2, 0 };
		dirPs.push_back(offsetP4 + dirVert);
		dirPs.push_back(offsetP1 + dirVert);
		dirPs.push_back(offsetP2 + dirVert);
		dirPs.push_back(offsetP3 + dirVert);

		int nParticles = 250;
		Vector3D posR = { 2,2,2 };
		Vector3D dirR = { 3,3,2 };
		float spawnDelay = 0.01;
		float lifetime = 1;
		float lifetimeR = 1;
		float mass = 1000;
		PxShape* partShape = CreateShape(PxSphereGeometry(0.5f));
		Vector4 colour = { 1,1,1,0.5 };

		for (int i = 0; i < 4; i++) {
			Vector3D pos = posPs[i];
			Vector3D dir = dirPs[i];
			ParticleSystem* partSys = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, mass, partShape, colour);
			particles.push_back(partSys);
			partSys->enable(true);
			partSys->addGen(force);
		}
	}

	virtual void update(double t) {
		force->update(t);
		for (auto ps : particles) ps->update(t);
	}

	virtual void move(Vector3D pos) {
		centerPos = pos;
		force->updatePos(pos);

		vector<Vector3D> posPs;
		Vector3D posVert = { 0, -r * 0.5f, 0 };
		posPs.push_back(offsetP1 + centerPos + posVert);
		posPs.push_back(offsetP2 + centerPos + posVert);
		posPs.push_back(offsetP3 + centerPos + posVert);
		posPs.push_back(offsetP4 + centerPos + posVert);
		for (int i = 0; i < 4; i++) {
			particles[i]->updatePos(posPs[i]);
		}
	};
private:
	float r;
	Vector3D centerPos;
	Vector3D offsetP1;
	Vector3D offsetP2;
	Vector3D offsetP3;
	Vector3D offsetP4;
};