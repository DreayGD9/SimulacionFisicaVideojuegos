#include "RigidBody_Dynamic.h"

#include "mainGame.h"

RigidBody_Dynamic::RigidBody_Dynamic(PxTransform transform, Vector3D lVelocity, Vector3D aVelocity, PxShape* shape, Vector4 colour, mainGame* game, float density) :
	tr(transform), s(shape), g(game) {
	rigid = g->getPhysics()->createRigidDynamic(tr);
	rigid->attachShape(*s);
	rigid->setLinearVelocity(PxVec3{ lVelocity.xV, lVelocity.yV, lVelocity.zV });
	rigid->setAngularVelocity(PxVec3{ aVelocity.xV, aVelocity.yV, aVelocity.zV });

	PxRigidBodyExt::updateMassAndInertia(*rigid, density);
	g->getScene()->addActor(*rigid);

	item = new RenderItem(s, rigid, colour);
}