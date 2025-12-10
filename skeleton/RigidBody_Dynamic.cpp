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

RigidBody_Dynamic::~RigidBody_Dynamic() {
	item->release();
	rigid->release();
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
	PxTransform transf = rigid->getGlobalPose();
	Vector3D pos = { transf.p.x, transf.p.y, transf.p.z };
	Vector3D vel = { lV.x, lV.y, lV.z };

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
		rigid->addForce(totalForce);
	}
}