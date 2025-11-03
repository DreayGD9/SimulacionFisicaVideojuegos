#pragma once

#include "ForceGenerator.h"
class FG_Wind : public ForceGenerator
{
public:
	FG_Wind(float wP, Vector3D wS) {
		windSpeed = wS;
		windStrength = wP;
	}

	virtual Vector3D getForce(float m, Vector3D p, Vector3D v) {
		//result = 𝑘1(𝑣𝑣 − 𝑣) + 𝑘2‖𝑣𝑣 − 𝑣 ‖(𝑣𝑣 − 𝑣)
		//Vector3D result = (wS - v)
	};
private:
	Vector3D windSpeed;
	float windStrength;
};

