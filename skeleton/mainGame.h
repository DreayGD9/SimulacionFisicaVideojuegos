#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "RigidBody_Static.h"
#include "RigidBody_Dynamic.h"
#include "ObjectSystem.h"
#include "FG_Library.h"
#include "AG_Library.h"

#include "Player.h"
#include "Enemy.h"

class mainGame
{
public:
	mainGame(PxPhysics* physics, PxScene* scene);
	~mainGame();

	void update(float t);

	void enablePhysics();
	void disablePhysics();

	void endGame();

	void createPlayer();
	void createEnemy();
	void createCameraShooter();

	void plrForward();
	void plrBackward();
	void plrStop();

	void enemiesFire();
	void cameraFire();

	void togglePlrSpeed();
	void toggleEnmSpeed();

	void toggleGravity();
	void toggleWind();
	void toggleWhirlwind();
	void explodeAll();

	PxPhysics* getPhysics() { return gPhysics; }
	PxScene* getScene() { return gScene; }

	static const bool GAME_DEBUG = false;

private:

	bool game;

	float deathY = -35;

	PxPhysics* gPhysics;
	PxScene* gScene;

	Player* plr;
	FG_PlrSpeed* plrSpeed;
	ParticleSystem* camshooter;

	vector<Enemy*> enemies;
	vector<ForceGenerator*> forceGens;
	vector<Particle*> independentParticles;
	vector<ParticleSystem*> partSystems;
	vector<RigidBody_Dynamic*> independentRigids;
	vector<ObjectSystem*> objSystems;

	vector<AestheticGenerator*> AGs;
};

