#pragma once
#include "RigidBody_Dynamic.h"
#include "ForceGenerator.h"
#include <vector>
#include <list>
#include <random>
#include <stdlib.h>

using namespace physx;

class ObjectSystem
{
public:
	ObjectSystem(int n,
		Vector3D sP,
		Vector3D sD,
		Vector3D sA,
		Vector3D pR,
		Vector3D dR,
		Vector3D aR,
		float spD,
		float sT,
		float rT,
		float pM,
		PxShape* s,
		Vector4 c,
		mainGame* g);
	~ObjectSystem() {};

	void enable(bool e) { enabled = e; };
	void toggleEnable() { enabled = !enabled; };
	void emit(int n);

	virtual void update(double t);

	void updatePos(Vector3D newPos);
	void updateDir(Vector3D newDir);
	Vector3D getPos() { return sPos; }
	void addGen(ForceGenerator* force);

	PxVec3 getTotalForce(Vector3D pos, Vector3D v);

protected:
	vector<unique_ptr<RigidBody_Dynamic>> objects;
	int nObjects, maxObjects;
	void integrate(double t);
	virtual void createObject();

private:

	bool enabled;

	PxShape* shape;
	Vector4 colour;
	Vector3D sPos, sDir, sAng, rPos, rDir, rAng;
	float sTime, rTime;
	float spDelay;
	float pMass;

	float lastSpawnT = 0;

	normal_distribution<float> dist;
	static default_random_engine gen;
	Vector3D genRandVec(Vector3D ini, Vector3D range);

	list<ForceGenerator*> forces;
	mainGame* game;
};