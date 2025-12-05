/*
#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
#include <vector>
#include <list>
#include <random>
#include <stdlib.h>

class ObjectSystem
{
public:
	ParticleSystem(int n,
		Vector3D sP,
		Vector3D sD,
		Vector3D pR,
		Vector3D dR,
		float spD,
		float sT,
		float rT,
		float pM,
		PxShape* s,
		Vector4 c);
	~ParticleSystem() {};

	void enable(bool e) { enabled = e; };
	void toggleEnable() { enabled = !enabled; };
	void emit(int n);

	virtual void update(double t);

	void updatePos(Vector3D newPos);
	void updateDir(Vector3D newDir);
	Vector3D getPos() { return sPos; }
	void addGen(ForceGenerator* force);

	Vector3D getAccel(float m, Vector3D pos, Vector3D v);

protected:
	vector<unique_ptr<Particle>> particles;
	int nParticles, maxParticles;
	void integrate(double t);
	virtual void createParticle();

private:

	bool enabled;

	PxShape* shape;
	Vector4 colour;
	Vector3D sPos, sDir, rPos, rDir;
	float sTime, rTime;
	float spDelay;
	float pMass;

	float lastSpawnT = 0;

	normal_distribution<float> dist;
	static default_random_engine gen;
	Vector3D genRandVec(Vector3D ini, Vector3D range);

	list<ForceGenerator*> forces;
};


*/