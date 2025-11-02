#include "Particle.h"

#include "ParticleSystem.h"
#include <iostream>

using namespace std;


Particle::Particle(PxShape* s, Vector3D p, Vector3D v, float m, float l, ParticleSystem* ps) : vel(v), mass(m), lifetime(l), partsys(ps) {
	tr = PxTransform({ p.x(), p.y(), p.z() });
	renderItem = new RenderItem(s, &tr, { 1,1,1,1 });
	timeAlive = 0;
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::addForce(Vector3D f) {
	forces.push_back(f);
}

void Particle::integrate(double t) {

	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Calcular aceleración en base a las fuerzas por la masa
	accel = partsys->getAccel(mass);

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

	// Actualizar tiempo de vida
	timeAlive += t;
}