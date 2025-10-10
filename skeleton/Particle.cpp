#include "Particle.h"
#include <iostream>

using namespace physx;
using namespace std;

Particle::Particle(Vector3D p, Vector3D v, Vector3D a) {
	PxShape* shape = CreateShape(PxSphereGeometry(1.0f));
	tr = PxTransform({ p.x(), p.y(), p.z() });
	renderItem = new RenderItem(shape, &tr, { 1,1,1,1 });
	vel = v;
	accel = a;
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	
	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Actualizar velocidad con aceleración
	vel += accel * t;

	// Damping
	//vel *= powf(damping, t);

	cout << vel.x() << " " << vel.y() << " " << vel.z() << endl;
	cout << tr.p.x << " " << tr.p.y << " " << tr.p.z << endl << endl;

	// Actualizar posición con velocidad
	tr.p.x += vel.x() * t;
	tr.p.y += vel.y() * t;
	tr.p.z += vel.z() * t;


}