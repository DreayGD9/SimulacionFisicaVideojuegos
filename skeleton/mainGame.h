#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Axis.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "FG_Library.h"

class mainGame
{
public:
	mainGame();
	~mainGame();

	void update(float t);

	void fireParticles(int n);
	void toggleParticles();
	void explodeAll();

	static const bool GAME_DEBUG = true;

private:
	vector<ParticleSystem*> partSystems;
	vector<ForceGenerator*> forceGens;
};

