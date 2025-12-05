#include "RigidBody_Dynamic.h"

#include "mainGame.h"

using namespace physx;

RigidBody_Dynamic::RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float density) :
	tr(transform), s(shape), g(game), d(density) {
	rigid = g->getPhysics()->createRigidDynamic(tr);
	rigid->attachShape(*s);
	rigid->setLinearVelocity(PxVec3{ lVelocity.xV, lVelocity.yV, lVelocity.zV });
	rigid->setAngularVelocity(PxVec3{ aVelocity.xV, aVelocity.yV, aVelocity.zV });
	
	PxRigidBodyExt::updateMassAndInertia(*rigid, d);
	g->getScene()->addActor(*rigid);

	item = new RenderItem(s, rigid, colour);

	timeAlive = 0;
}

void RigidBody_Dynamic::integrate(double t) {
	// Actualizar tiempo de vida
	if (lifetime >= 0) {
		timeAlive += t;
	}

	// Fuerzas
	for (auto fg : forces) {
		physx::PxVec3 lV = rigid->getLinearVelocity();
		Vector3D pos = { tr.p.x, tr.p.y, tr.p.z };
		Vector3D vel = { lV.x, lV.y, lV.z };
		Vector3D force = fg->getForce(rigid->getMass(), pos, vel);
		rigid->addForce({force.xV, force.yV, force.zV});
	}
}