#include "Particle.h"
#include <iostream>

using namespace physx;
using namespace std;

Particle::Particle(Vector3D p, Vector3D v, float m) : vel(v), mass(m) {
	PxShape* shape = CreateShape(PxSphereGeometry(1.0f));
	tr = PxTransform({ p.x(), p.y(), p.z() });
	renderItem = new RenderItem(shape, &tr, { 1,1,1,1 });
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::addGenerator(ForceGenerator* g) {
	forceGens.push_back(g);
}

void Particle::remGenerator(ForceGenerator* g) {
	forceGens.remove(g);
}

void Particle::updateForces() {
	accel = { 0,0,0 };
	for (auto fg : forceGens) {
		accel += fg->getForce() * mass;
	}
}

void Particle::integrate(double t) {
	
	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Calcular aceleración en base a las fuerzas por la masa
	accel = { 0,0,0 };
	
	// Aplicar fuerzas en base a generadores para crear la aceleración
	updateForces();

	// Actualizar velocidad con aceleración
	vel += accel * t;

	// Damping
	//vel *= powf(damping, t);

	if (DEBUG) 
		cout << "V: " << vel << " | "
		<< "A: " << accel << " | "
		<< "T: (" << tr.p.x << ", " << tr.p.y << ", " << tr.p.z << ")" << endl << endl;

	// Actualizar posición con velocidad
	tr.p.x += vel.x() * t;
	tr.p.y += vel.y() * t;
	tr.p.z += vel.z() * t;


}