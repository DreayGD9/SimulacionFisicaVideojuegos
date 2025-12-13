#include "ParticleSystem.h"
#include "mainGame.h"
#include <iostream>

using namespace std;
default_random_engine ParticleSystem::gen(std::random_device{}());

ParticleSystem::ParticleSystem(int n,
	Vector3D sP,
	Vector3D sD,
	Vector3D pR,
	Vector3D dR,
	float spD,
	float sT,
	float rT,
	float pM,
	PxShape* s,
	Vector4 c) {

	enabled = false;

	nParticles = 0;
	maxParticles = n;

	rPos = pR;
	rDir = dR;
	sPos = sP;
	sDir = sD;
	spDelay = spD;
	sTime = sT;
	rTime = rT;
	pMass = pM;

	shape = s;
	colour = c;

	dist = std::normal_distribution<float>(0, 1);
}

Vector3D ParticleSystem::genRandVec(Vector3D ini, Vector3D range) {
	Vector3D sol;
	sol.xV = dist(gen) * range.xV + ini.xV;
	sol.yV = dist(gen) * range.yV + ini.yV;
	sol.zV = dist(gen) * range.zV + ini.zV;
	return sol;
}

void ParticleSystem::createParticle() {
	Vector3D pP = genRandVec(sPos, rPos);
	Vector3D pV = genRandVec(sDir, rDir);
	float pL = sTime + dist(gen) * rTime;
	particles.push_back(make_unique<Particle>(pP, pV, pMass, pL, this, shape, colour));
	nParticles++;
}

void ParticleSystem::emit(int n) {
	int amount;
	if (n >= maxParticles) amount = maxParticles;
	else amount = n;
	for (int i = 0; i < n; i++) createParticle();
}

void ParticleSystem::clear() {
	for (int i = 0; i < particles.size(); i++)
	{
		particles.erase(particles.begin() + i);
		nParticles--;
	}
}

void ParticleSystem::update(double t) {

	if (enabled) {
		if (lastSpawnT > spDelay && nParticles < maxParticles) {
			lastSpawnT = 0;
			createParticle();
		}
		else {
			lastSpawnT += t;
		}
	}

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->canExpire())
		{
			particles.erase(particles.begin() + i);
			nParticles--;
		
		}
		else
		{
			i++;
		}
	}

	integrate(t);
}

void ParticleSystem::updatePos(Vector3D newPos) { 
	sPos = newPos;
}
void ParticleSystem::updateDir(Vector3D newDir) {
	sDir = newDir;
}

void ParticleSystem::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}

Vector3D ParticleSystem::getAccel(float m, Vector3D p, Vector3D v) {
	Vector3D a = { 0,0,0 };
	for (auto f : forces) {
		Vector3D force = f->getForce(m, p, v);
		a += force;
	}
	return a;
}

void ParticleSystem::integrate(double t) {
	for (auto& p : particles)
	{
		p->integrate(t);
	}
}