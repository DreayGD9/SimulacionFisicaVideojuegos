#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Axis.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "FG_Library.h"

#include "Player.h"
#include "Enemy.h"

class mainGame
{
public:
	mainGame();
	~mainGame();

	void update(float t);

	void createPlayer();
	void createEnemy();

	void plrForward();
	void plrBackward();
	void plrStop();

	void enemiesFire();

	void togglePlrSpeed();
	void toggleEnmSpeed();
	void toggleGravity();
	void toggleWind();
	void toggleWhirlwind();
	void explodeAll();

	static const bool GAME_DEBUG = false;

private:

	Player* plr;
	FG_PlrSpeed* plrSpeed;

	vector<Enemy*> enemies;
	vector<ForceGenerator*> forceGens;
};

