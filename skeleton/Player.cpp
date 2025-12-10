#include "Player.h"
#include "mainGame.h"

#include "ForceGenerator.h"

Player::Player(PxTransform tr, float m, float ms, PxShape* s, Vector4 c, mainGame* g) : 
	RigidBody_Dynamic(tr, { 0,0,0 }, { 0,0,0 }, s, c, g, -1, m), maxSpd(ms), horizontallyLocked(true), game(g) {
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
	if (os != nullptr) { // Si tiene sistema de partículas asociado
		PxVec3 totalForce = os->getTotalForce(pos, vel);

		rigid->addForce(totalForce);
	}
	else { // Si es un objeto independiente
		PxVec3 totalForce = { 0,0,0 };
		for (auto f : forces) {
			Vector3D force = f->getForceMassless(pos, vel);
			totalForce += {force.xV, force.yV, force.zV};
		}
		cout << totalForce.x << " " << totalForce.y << " " << totalForce.z << " | ";
		cout << forces.size() << " " << vel << endl;
		rigid->addForce(totalForce);
	}
	
}

void Player::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}

Vector3D Player::returnPos() {
	PxTransform transf = rigid->getGlobalPose();
	return { transf.p.x, transf.p.y, transf.p.z };
}