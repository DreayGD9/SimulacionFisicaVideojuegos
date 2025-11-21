#include "Particle.h"

#include "ParticleSystem.h"
#include <iostream>

using namespace std;

Particle::Particle(Vector3D p, Vector3D v, float m, float l, ParticleSystem* ps, PxShape* s, Vector4 c) : vel(v), mass(m), lifetime(l), partsys(ps) {
	tr = PxTransform({ p.x(), p.y(), p.z() });
	renderItem = new RenderItem(s, &tr, c);
	timeAlive = 0;
	anchored = false;
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {

	// Euler semi-implícito
	if (t <= 0.0f) return;

	if (!anchored) { // Moverla sólo si está anclada
		// Calcular aceleración en base a las fuerzas por la masa
		Vector3D pos = { tr.p.x, tr.p.y, tr.p.z };
		if (partsys != nullptr) { // Si tiene sistema de partículas asociado
			accel = partsys->getAccel(mass, pos, vel);
		}
		else { // Si es una partícula independiente
			accel = { 0,0,0 };
			for (auto f : forces) {
				accel += f->getForce(mass, pos, vel);
			}
		}

		// Actualizar velocidad con aceleración
		vel += accel * t;

		// Damping
		vel *= powf(damping, t);

		// Actualizar posición con velocidad
		tr.p.x += vel.x() * t;
		tr.p.y += vel.y() * t;
		tr.p.z += vel.z() * t;
	}

	// Actualizar tiempo de vida
	if (lifetime >= 0) {
		timeAlive += t;
	}
}