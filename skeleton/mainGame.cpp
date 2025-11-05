#include "mainGame.h"

mainGame::mainGame() {
	// Force generators

	FG_Constant* FG_gravity = new FG_Constant("GRAVITY", Vector3D(0, -9.8, 0), false, true);
	//forceGens.push_back(FG_gravity);
	//FG_Wind* FG_wind1 = new FG_Wind("WIND1", 1000, { 0, 0, 1 }, true, { 40,0,0 }, 20);
	//forceGens.push_back(FG_wind1);
	//FG_Whirlwind* FG_whirlwind1 = new FG_Whirlwind("WHIRLWIND1", 100, {0,0,0}, 20);
	//forceGens.push_back(FG_gravity);
	FG_Explosion* FG_explosion1 = new FG_Explosion("EXPLOSION1", 50000, 100, 3, false, false, { 0, 0, 0 }, 20, 0.15);
	forceGens.push_back(FG_explosion1);

	// Axis

	Axis axis = Axis(0.5, 10, true, 0.5);

	// Particlesystem

	int nParticles = 500;
	Vector3D pos = { -40,0,0 };
	Vector3D dir = { 20,20,0 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 2,2,2 };
	float spawnDelay = 0.01;
	float lifetime = 5;
	float lifetimeR = 1;
	PxShape* partShape = CreateShape(PxSphereGeometry(0.5f));
	Vector4 colour = { 1,1,1,1 };
	ParticleSystem* partSys1 = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, partShape, colour);

	partSys1->addGen(FG_gravity);
	partSys1->addGen(FG_explosion1);

	partSystems.push_back(partSys1);

	partSys1->enable(true);
}

void mainGame::update(float t) {
	for (auto s : partSystems) {
		s->update(t);
	}

	for (auto fg : forceGens) {
		fg->update(t);
	}
}

void mainGame::fireParticles(int n) {
	for (auto s : partSystems) {
		s->emit(n);
	}
}

void mainGame::toggleParticles() {
	for (auto s : partSystems) {
		s->toggleEnable();
	}
}

void mainGame::explodeAll() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_EXPLOSION) {
			auto* expl = static_cast<FG_Explosion*>(fg);
			expl->explode();
		}
	}
}