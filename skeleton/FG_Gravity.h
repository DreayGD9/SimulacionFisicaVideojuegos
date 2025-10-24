#pragma once

#include "ForceGenerator.h"

class FG_Gravity : public ForceGenerator
{
public:
	FG_Gravity() {
		name = "GRAVITY";
		force = { 0, -9.8, 0 };
	}
};

