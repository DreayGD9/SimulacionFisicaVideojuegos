#include "ObjectSystem.h"
#include "mainGame.h"
#include <iostream>

using namespace std;
default_random_engine ObjectSystem::gen(std::random_device{}());

ObjectSystem::ObjectSystem(int n,
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
	mainGame* g) {

	enabled = false;

	nObjects = 0;
	maxObjects = n;

	sPos = sP;
	sDir = sD;
	sAng = sA;
	rPos = pR;
	rDir = dR;
	rAng = aR;
	spDelay = spD;
	sTime = sT;
	rTime = rT;
	pMass = pM;

	shape = s;
	colour = c;

	dist = std::normal_distribution<float>(0, 1);

	game = g;
}

Vector3D ObjectSystem::genRandVec(Vector3D ini, Vector3D range) {
	Vector3D sol;
	sol.xV = dist(gen) * range.xV + ini.xV;
	sol.yV = dist(gen) * range.yV + ini.yV;
	sol.zV = dist(gen) * range.zV + ini.zV;
	return sol;
}

void ObjectSystem::createObject() {
	Vector3D pos = genRandVec(sPos, rPos);
	PxTransform transf = PxTransform(pos.xV, pos.yV, pos.zV);
	Vector3D lV = genRandVec(sDir, rDir);
	Vector3D aV = genRandVec(sAng, rAng);
	float pL = sTime + dist(gen) * rTime;
	objects.push_back(make_unique<RigidBody_Dynamic>(transf, lV, aV, shape, colour, game, pL, pMass));
	nObjects++;
}

void ObjectSystem::emit(int n) {
	int amount;
	if (n >= maxObjects) amount = maxObjects;
	else amount = n;
	for (int i = 0; i < n; i++) createObject();
}

void ObjectSystem::update(double t) {

	if (enabled) {
		if (lastSpawnT > spDelay && nObjects < maxObjects) {
			lastSpawnT = 0;
			createObject();
		}
		else {
			lastSpawnT += t;
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->canExpire())
		{
			objects.erase(objects.begin() + i);
			nObjects--;

		}
		else
		{
			i++;
		}
	}

	integrate(t);
}

void ObjectSystem::updatePos(Vector3D newPos) {
	sPos = newPos;
}
void ObjectSystem::updateDir(Vector3D newDir) {
	sDir = newDir;
}

void ObjectSystem::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}

PxVec3 ObjectSystem::getTotalForce(Vector3D pos, Vector3D v) {
	PxVec3 tf = { 0,0,0 };
	for (auto f : forces) {
		Vector3D force = f->getForceMassless(pos, v);
		tf += {force.xV, force.yV, force.zV};
	}
	return tf;
}

void ObjectSystem::integrate(double t) {
	for (auto& p : objects)
	{
		p->integrate(t);
	}
}