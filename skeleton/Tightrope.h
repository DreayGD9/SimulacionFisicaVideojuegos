#pragma once

#include "RigidBody_Static.h"
#include "mainGame.h"

class Tightrope
{
public:
	Tightrope(Vector3D pos, float thickness, float length, Vector4 colour, mainGame* g) {
		PxShape* ropeShape = CreateShape(PxBoxGeometry(length, thickness, thickness), g->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f));
		PxShape* topperShape = CreateShape(PxBoxGeometry(thickness * 3, length, 50), g->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f));

		PxTransform ropeTr = PxTransform(pos.xV, pos.yV, pos.zV);
		PxTransform topperTr1 = PxTransform(pos.xV + length, pos.yV, pos.zV);
		PxTransform topperTr2 = PxTransform(pos.xV - length, pos.yV, pos.zV);

		rope = new RigidBody_Static(ropeTr, ropeShape, colour, g);
		topper1 = new RigidBody_Static(topperTr1, topperShape, colour, g);
		topper2 = new RigidBody_Static(topperTr2, topperShape, colour, g);
	}

private:
	RigidBody_Static* rope;
	RigidBody_Static* topper1;
	RigidBody_Static* topper2;
};