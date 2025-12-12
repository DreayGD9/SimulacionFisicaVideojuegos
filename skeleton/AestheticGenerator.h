#pragma once
#include "ParticleSystem.h"
#include "ObjectSystem.h"
#include "FG_Library.h"

class AestheticGenerator
{
public:
	AestheticGenerator(Vector3D pos) : p(pos) {};

	virtual void update(double t) {};

	virtual void move(Vector3D pos) {};

	void setActive(bool a) {
		force->setActive(a);
		for (auto ps : particles) ps->enable(a);
	}

	void updateDebugView() {
		force->updateDebugView();
	}

	ForceGenerator* getFG() { return force; };


protected:

	Vector3D p;

	vector<ParticleSystem*> particles;
	ForceGenerator* force;
};

