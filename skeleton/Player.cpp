#include "Player.h"
#include "mainGame.h"

#include "ForceGenerator.h"

Player::Player(PxTransform tr, float m, float ms, PxShape* s, Vector4 c, mainGame* g) : 
	RigidBody_Dynamic(tr, { 0,0,0 }, { 0,0,0 }, s, c, g, -1, m), maxSpd(ms), horizontallyLocked(true), game(g) {

	lockY = true;
}

void Player::update(float t) {
	integrate(t);
}

void Player::integrate(float t) {

	physx::PxVec3 lV = rigid->getLinearVelocity();
	PxTransform transf = rigid->getGlobalPose();
	Vector3D pos = { transf.p.x, transf.p.y, transf.p.z };
	Vector3D vel = { lV.x, lV.y, lV.z };

	// Limitación de velocidad máxima
	if (vel.xV > maxSpd) vel.xV = maxSpd;
	else if (vel.xV < -maxSpd) vel.xV = -maxSpd;

	if (vel.zV > maxSpd) vel.zV = maxSpd;
	else if (vel.zV < -maxSpd) vel.zV = -maxSpd;

	rigid->setLinearVelocity({ vel.xV, vel.yV, vel.zV });

	// Fuerzas
	PxVec3 totalForce = { 0,0,0 };
	for (auto f : forces) {
		Vector3D force = f->getForceMassless(pos, vel);
		totalForce += {force.xV, force.yV, force.zV};
	}

	// Bloqueo de eje horizontal: mantener sobre la cuerda
	if (lockY) totalForce.y = 0.0f;

	rigid->addForce(totalForce);
	
}

void Player::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}