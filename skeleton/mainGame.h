#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Axis.h"
#include "Particle.h"
#include "ParticleSystem.h"

//#include "FG_Constant.h"
//#include "FG_Wind.h"
//#include "FG_Whirlwind.h"
//#include "FG_Explosion.h"
#include "FG_Library.h"

class mainGame
{
public:
	mainGame();
	~mainGame();

	void update(float t);

	static const bool GAME_DEBUG = false;

private:
	vector<ParticleSystem*> partSystems;
	vector<ForceGenerator*> forceGens;
};

