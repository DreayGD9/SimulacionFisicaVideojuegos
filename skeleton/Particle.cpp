#include "Particle.h"
#include <iostream>

using namespace physx;
using namespace std;

Particle::Particle(Vector3D p, Vector3D v, float m) : vel(v), mass(m) {
	PxShape* shape = CreateShape(PxSphereGeometry(1.0f));
	tr = PxTransform({ p.x(), p.y(), p.z() });
	renderItem = new RenderItem(shape, &tr, { 1,1,1,1 });
	forces.push_back(gravity);
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::addForce(Force f) {
	forces.push_back(f);
}

void Particle::integrate(double t) {
	
	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Calcular aceleración en base a las fuerzas por la masa
	accel = { 0,0,0 };
	for (auto f : forces) {
		accel += (f.getForce() * mass);
	}

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