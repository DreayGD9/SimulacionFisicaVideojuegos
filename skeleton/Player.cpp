#include "Player.h"

Player::Player(Vector3D p, float m, float ms, PxShape* s, Vector4 c) : Particle(p, {0,0,0}, m, 1, nullptr, s, c),  maxSpd(ms) {
	horizontallyLocked = true;
}

void Player::update(float t) {
	integrate(t);
}

void Player::integrate(float t) {
	// Euler semi-implícito
	if (t <= 0.0f) return;

	// Calcular aceleración en base a las fuerzas por la masa
	accel = getAccel();

	// Actualizar velocidad con aceleración
	vel += accel * t;

	// Limitación de velocidad máxima
	if (vel.xV > maxSpd) vel.xV = maxSpd;
	else if (vel.xV < -maxSpd) vel.xV = -maxSpd;

	if (vel.zV > maxSpd) vel.zV = maxSpd;
	else if (vel.zV < -maxSpd) vel.zV = -maxSpd;

	cout << vel << " | " << accel << endl;

	// Damping
	//vel *= powf(damping, t);

	// Actualizar posición con velocidad
	tr.p.x += vel.x() * t;
	if (!horizontallyLocked) tr.p.y += vel.y() * t;
	tr.p.z += vel.z() * t;
}

void Player::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}

Vector3D Player::getAccel() {
	Vector3D a = { 0,0,0 };
	Vector3D pos = { tr.p.x, tr.p.y, tr.p.z };
	for (auto f : forces) {
		Vector3D force = f->getForce(mass, pos, vel);
		a += force;
	}
	return a;
}