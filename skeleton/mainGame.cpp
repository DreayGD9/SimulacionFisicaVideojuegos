#include "mainGame.h"

mainGame::mainGame() {

	// Axis

	if (GAME_DEBUG) Axis axis = Axis(0.5, 10, true, 0.5);

	// Force generators

	FG_Constant* FG_gravity = new FG_Constant("GRAVITY", Vector3D(0, -9.8, 0), false, true);
	forceGens.push_back(FG_gravity);

	// Tightrope

	PxTransform* TransformC = new PxTransform({ 0, -5, 0 });
	PxShape* XaxisShape = CreateShape(PxBoxGeometry(1000, 0.5, 0.5));
	RenderItem* Tightrope = new RenderItem(XaxisShape, TransformC, { 1,0,0,1 });

	// Player

	createPlayer();

	// Enemies

	createEnemy();


	/*
	
	--------------------------------------------------------------------
	EJEMPLOS DE USO DE LOS GENERADORES DE VIENTO, TORBELLINO Y EXPLOSIÓN
	EJEMPLO DE SISTEMA DE PARTÍCULAS
	--------------------------------------------------------------------
	


	FG_Wind* FG_wind1 = new FG_Wind("WIND1", 1000, { 0, 0, 1 }, false, true, { 0,0,0 }, 40);
	forceGens.push_back(FG_wind1);
	FG_Whirlwind* FG_whirlwind1 = new FG_Whirlwind("WHIRLWIND1", 100, false, { 0,0,0 }, 20);
	forceGens.push_back(FG_whirlwind1);
	FG_Explosion* FG_explosion1 = new FG_Explosion("EXPLOSION1", 50000, 100, 3, false, false, { 0, 0, 0 }, 30, 0.15);
	forceGens.push_back(FG_explosion1);

	int nParticles = 500;
	Vector3D pos = { -40,0,0 };
	Vector3D dir = { 20,10,5 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 2,2,2 };
	float spawnDelay = 0.01;
	float lifetime = 5;
	float lifetimeR = 1;
	float mass = 10;
	PxShape* partShape = CreateShape(PxSphereGeometry(0.5f));
	Vector4 colour = { 1,1,1,1 };
	ParticleSystem* partSys1 = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, mass, partShape, colour);

	partSys1->addGen(FG_gravity);
	partSys1->addGen(FG_wind1);
	partSys1->addGen(FG_whirlwind1);
	partSys1->addGen(FG_explosion1);

	partSystems.push_back(partSys1);

	partSys1->enable(true);

	*/
}

void mainGame::update(float t) {
	for (auto e : enemies) {
		e->update(t);
	}

	for (auto fg : forceGens) {
		fg->update(t);
	}

	for (auto ps : partSystems) {
		ps->update(t);
	}

	plr->update(t);
}

void mainGame::createPlayer() {
	Vector3D pos = { 0,0,0 };
	float mass = 10;
	float maxSpd = 25;
	PxShape* shape = CreateShape(PxSphereGeometry(5));
	Vector4 colour = { 1,1,1,1 };
	plr = new Player(pos, mass, maxSpd, shape, colour);

	plrSpeed = new FG_PlrSpeed("PLR_SPEED", maxSpd * 100, maxSpd * 10);
	forceGens.push_back(plrSpeed);
	plr->addGen(plrSpeed);
}

void mainGame::createEnemy() {
	
	Vector3D pos = { 0,0,-50 };
	float mass = 10;
	float maxSpd = 50;
	PxShape* shape = CreateShape(PxSphereGeometry(5));
	Vector4 colour = { 1,0,0,0.5 };
	float shotDelay = 0.01;
	float shotPower = 100;

	Enemy* enemy = new Enemy(pos, mass, maxSpd, shape, colour, shotDelay, shotPower, plr);
	enemies.push_back(enemy);

	FG_PlrSpeed* enemySpd = new FG_PlrSpeed("ENM_SPEED", maxSpd * 100, maxSpd * 10);
	forceGens.push_back(enemySpd);
	enemy->addGen(enemySpd);

	for (auto fg : forceGens) {
		if (fg->getType() != FG_PLRSPEED) enemy->addGenToShots(fg);
	}
}

void mainGame::plrForward() {
	plrSpeed->forward();
}
void mainGame::plrBackward() {
	plrSpeed->backward();
}
void mainGame::plrStop() {
	plrSpeed->stop();
}

void mainGame::enemiesFire() {
	for (auto e : enemies) {
		e->fire();
	}
}

void mainGame::togglePlrSpeed() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_PLRSPEED && fg->getName() == "PLR_SPEED") {
			fg->toggleActive();
		}
	}
}

void mainGame::toggleEnmSpeed() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_PLRSPEED && fg->getName() == "ENM_SPEED") {
			fg->toggleActive();
		}
	}
}

void mainGame::toggleGravity() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_CONSTANT && fg->getName() == "GRAVITY") {
			fg->toggleActive();
		}
	}
}

void mainGame::toggleWind() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_WIND) {
			fg->toggleActive();
		}
	}
}

void mainGame::toggleWhirlwind() {
	for (auto fg : forceGens) {
		if (fg->getType() == FG_WHIRLWIND) {
			fg->toggleActive();
		}
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