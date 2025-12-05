#include "mainGame.h"

#include "Floor.h"
#include "Axis.h"

mainGame::mainGame(PxPhysics* physics, PxScene* scene) {

	gPhysics = physics;
	gScene = scene;

	// Axis

	if (GAME_DEBUG) Axis axis = Axis(0.5, 10, true, 0.5);

	// Force generators

	FG_Constant* FG_gravity = new FG_Constant("GRAVITY", Vector3D(0, -9.8, 0), false, true);
	forceGens.push_back(FG_gravity);

	// Tightrope

	PxTransform* RopeTransform = new PxTransform({ 0, -5, 0 });
	PxShape* RopeShape = CreateShape(PxBoxGeometry(1000, 0.5, 0.5));
	RenderItem* Tightrope = new RenderItem(RopeShape, RopeTransform, { 1,0,0,1 });

	// Player

	createPlayer();

	// Enemies

	createEnemy();

	// Disparador desde cámara (requisitos enunciado)

	createCameraShooter();

	// Suelo

	PxTransform FloorTransform = PxTransform({ 0, -20, 0 });
	Floor floor = Floor(FloorTransform, 100, 100, 1, { 1,1,1,1 }, this);

	/*
	// Demo de muelles

	Vector3D pP1 = { 0,-10,0 };
	Vector3D pP2 = { 0,0,0 };
	Vector3D pV = { 0,0,0 };
	float pMass = 10;
	float pL = -1;
	PxShape* shape = CreateShape(PxSphereGeometry(0.5f));
	Vector4 colour = { 1,1,1,1 };

	//Particle* p1 = new Particle(pP1, pV, pMass, pL, nullptr, shape, colour);
	//Particle* p2 = new Particle(pP2, pV, pMass, pL, nullptr, shape, colour);
	//p1->setAnchored(true);
	//independentParticles.push_back(p1);
	//independentParticles.push_back(p2);
	//float k = 1;
	//float length = 10;
	//FG_Spring* spring1 = new FG_Spring("SPRING1", k, length, p2, true);
	//FG_Spring* spring2 = new FG_Spring("SPRING2", k, length, p1, true);
	//p1->addGen(spring1);
	//p1->addGen(FG_gravity);
	//p2->addGen(spring2);
	//p2->addGen(FG_gravity);
	//forceGens.push_back(spring1);
	//forceGens.push_back(spring2);

	Particle* pS = new Particle(pP1, pV, pMass, pL, nullptr, shape, colour);
	pS->setDamping(0.5);
	independentParticles.push_back(pS);
	float k = 1;
	float length = 20;
	FG_Spring* FG_spring = new FG_Spring("SPRING_A", k, length, nullptr, true, true, { 0,0,0 });
	pS->addGen(FG_spring);
	pS->addGen(FG_gravity);
	forceGens.push_back(FG_spring);

	int nParticles = 500;
	Vector3D pos = { -40,0,0 };
	Vector3D dir = { 0,-20,0 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 2,2,2 };
	float spawnDelay = 0.01;
	float lifetime = 5;
	float lifetimeR = 1;
	float mass = 10;
	PxShape* partShape = CreateShape(PxSphereGeometry(0.5f));
	ParticleSystem* partSys1 = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, mass, partShape, colour);

	partSys1->addGen(FG_gravity);
	partSys1->addGen(FG_spring);

	partSystems.push_back(partSys1);
	partSys1->enable(true);
	*/

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

	for (auto p : independentParticles) {
		p->integrate(t);
	}
	cout << endl;

	for (auto ps : partSystems) {
		ps->update(t);
	}

	plr->update(t);

	if (camshooter != nullptr) {
		PxVec3 camE = GetCamera()->getEye();
		PxVec3 camD = GetCamera()->getDir();
		Vector3D pos = { camE.x, camE.y, camE.z };
		Vector3D dir = { camD.x, camD.y, camD.z };
		float pow = 50;
		camshooter->updatePos(pos);
		camshooter->updateDir(dir * pow);
	}
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

void mainGame::createCameraShooter() {
	int nParticles = 500;
	Vector3D pos = { 0,0,0 };
	Vector3D dir = { 0,0,0 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 0,0,0 };
	float spawnDelay = 0.01;
	float lifetime = 5;
	float lifetimeR = 1;
	float mass = 10;
	PxShape* partShape = CreateShape(PxSphereGeometry(0.5f));
	Vector4 colour = { 1,1,1,0.5 };
	camshooter = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, mass, partShape, colour);

	for (auto fg : forceGens) {
		if (fg->getType() != FG_PLRSPEED) camshooter->addGen(fg);
	}

	partSystems.push_back(camshooter);
	camshooter->enable(false);
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

void mainGame::cameraFire() {
	if (camshooter != nullptr) {
		camshooter->emit(1);
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