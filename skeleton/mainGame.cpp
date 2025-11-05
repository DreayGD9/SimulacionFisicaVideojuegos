#include "mainGame.h"

mainGame::mainGame() {
	// Force generators

	FG_Constant* FG_gravity = new FG_Constant("GRAVITY", Vector3D(0, -9.8, 0), false);
	forceGens.push_back(FG_gravity);
	//FG_Wind* FG_wind1 = new FG_Wind("WIND1", 1000, { 0, 0, 1 }, true, { 40,0,0 }, 20);
	//forceGens.push_back(FG_wind1);
	//FG_Whirlwind* FG_whirlwind1 = new FG_Whirlwind("WHIRLWIND1", 100, {0,0,0}, 20);
	//forceGens.push_back(FG_gravity);
	FG_Explosion* FG_explosion1 = new FG_Explosion("EXPLOSION1", 50000, 100, 3, { 0,0,0 }, 20, 0.15);
	forceGens.push_back(FG_explosion1);

	// Axis

	Axis axis = Axis(0.5, 10, true, 0.5);

	// Particlesystem

	PxShape* pS = CreateShape(PxSphereGeometry(0.5f));
	Vector4 col = { 1,1,1,1 };
	ParticleSystem* partSys1 = new ParticleSystem(
		500,
		{ -40,0,0 },
		{ 20,10,0 },
		{ 0,0,0 },
		{ 1,1,1 },
		0.01,
		5,
		1,
		pS,
		col
	);

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