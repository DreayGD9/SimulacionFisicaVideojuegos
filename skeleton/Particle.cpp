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

Vector3D Particle::generateAccel() {
	Vector3D a = { 0,0,0 };
	if (DEBUG) cout << "FGs affecting this particle: " << endl;
	for (auto fg : forceGens) {
		if (DEBUG) cout << "\t" << fg->getName() << " " << fg->getForce() << endl;
		a += fg->getForce() * mass;
	}
	return a;

	// NOTA: mover vector de generadores al sistema de partículas.
	// Cada partícula debe tener un puntero al sistema que las crea.
}

void Particle::integrate(double t) {
	
	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Calcular aceleración en base a las fuerzas por la masa
	accel = generateAccel();

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