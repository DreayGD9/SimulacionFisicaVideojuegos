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

class mainGame
{
public:
	mainGame();
	~mainGame();

	void update(float t);

	void createPlayer();
	void createLaunchers();

	void plrForward();
	void plrBackward();
	void plrStop();

	void fireParticles(int n);
	void toggleParticles();

	void toggleGravity();
	void toggleWind();
	void toggleWhirlwind();
	void explodeAll();

	static const bool GAME_DEBUG = true;

private:

	Player* plr;
	FG_PlrSpeed* plrSpeed;

	//ParticleSystem* launcher1;

	vector<ParticleSystem*> launchers;
	vector<ForceGenerator*> forceGens;
};

