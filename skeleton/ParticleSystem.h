#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
#include <vector>
#include <list>
#include <random>
#include <stdlib.h> 

class ParticleSystem
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
		PxShape* s,
		Vector4 c);
	~ParticleSystem() {};

	void enable(bool e) { enabled = e; };
	void emit(int n);

	virtual void update(double t);

	void updatePos(Vector3D newPos) { sPos = newPos; }
	void updateDir(Vector3D newDir) { sDir = newDir; }
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
	float yInclination;

	float lastSpawnT = 0;

	normal_distribution<float> dist;
	static default_random_engine gen;
	Vector3D genRandVec(Vector3D ini, Vector3D range);

	list<ForceGenerator*> forces;

};

