#include "RigidBody_Static.h"

#include "mainGame.h"

RigidBody_Static::RigidBody_Static(PxTransform transform, PxShape* shape, Vector4 colour, mainGame* game) : tr(transform), s(shape), g(game) {
	rigid = g->getPhysics()->createRigidStatic(tr);
	rigid->attachShape(*s);
	g->getScene()->addActor(*rigid);

	item = new RenderItem(s, rigid, colour);
}