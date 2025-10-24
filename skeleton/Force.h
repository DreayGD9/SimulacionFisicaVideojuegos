
#include <string>

#pragma once
#include "vector3D.h"

class Force
{
public:
	Force(string name, Vector3D force) : n(name), f(force){}

	string getName() { return n; };
	Vector3D getForce() { return f; };
private:
	string n;
	Vector3D f;
};

