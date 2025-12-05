#include "RigidBody_Dynamic.h"

#include "mainGame.h"
#include "ObjectSystem.h"

using namespace physx;

RigidBody_Dynamic::RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float life, float density, ObjectSystem* objectsys) :
	tr(transform), s(shape), g(game), d(density) {
	rigid = g->getPhysics()->createRigidDynamic(tr);
	rigid->attachShape(*s);
	rigid->setLinearVelocity(PxVec3{ lVelocity.xV, lVelocity.yV, lVelocity.zV });
	rigid->setAngularVelocity(PxVec3{ aVelocity.xV, aVelocity.yV, aVelocity.zV });

	PxRigidBodyExt::updateMassAndInertia(*rigid, d);
	g->getScene()->addActor(*rigid);

	item = new RenderItem(s, rigid, colour);

	timeAlive = 0;
	lifetime = life;
	os = objectsys;
}

void RigidBody_Dynamic::integrate(double t) {
	// Actualizar tiempo de vida
	if (lifetime >= 0) {
		timeAlive += t;
	}

	// Fuerzas
	for (auto fg : forces) {

	}

	physx::PxVec3 lV = rigid->getLinearVelocity();
	Vector3D pos = { tr.p.x, tr.p.y, tr.p.z };
	cout << pos << " ";
	Vector3D vel = { lV.x, lV.y, lV.z };
	float mass = rigid->getMass() / 100;

	if (os != nullptr) { // Si tiene sistema de partículas asociado
		PxVec3 totalForce = os->getTotalForce(mass, pos, vel);

		rigid->addForce(totalForce);
		cout << totalForce.x << "," << totalForce.y << "," << totalForce.z << "," << endl;
	}
	else { // Si es un objeto independiente
		PxVec3 totalForce = { 0,0,0 };
		for (auto f : forces) {
			Vector3D force = f->getForce(mass, pos, vel);
			totalForce += {force.xV, force.yV, force.zV};
		}
		rigid->addForce(totalForce);
		cout << totalForce.x << "," << totalForce.y << "," << totalForce.z << "," << endl;
	}
}