#include "Enemy.h"
#include "Player.h"
#include "FG_Library.h"

Enemy::Enemy(Vector3D p, float m, float ms, PxShape* s, Vector4 c, float d, Player* pl) : Particle(p, { 0,0,0 }, m, 1, nullptr, s, c), maxSpd(ms), player(pl), horizontallyLocked(true), shotDelay(d) {
	int nParticles = 100;
	Vector3D pos = { 0,0,0 };
	Vector3D dir = { 20,10,5 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 2,2,2 };
	float spawnDelay = 0.01;
	float lifetime = 5;
	float lifetimeR = 1;
	PxShape* partShape = CreateShape(PxBoxGeometry(0.5, 0.5, 0.5));
	Vector4 colour = { 1,1,1,1 };
	launcher = new ParticleSystem(nParticles, pos, dir, posR, dirR, spawnDelay, lifetime, lifetimeR, partShape, colour);
	launcher->enable(false);
}

void Enemy::update(float t) {

	// Attempt matching X axis position of player

	Vector3D playerPos = player->returnPos();

	for (auto fg : forces) {
		if (fg->getType() == FG_PLRSPEED && fg->getName() == "ENM_SPEED") {
			auto* spd = static_cast<FG_PlrSpeed*>(fg);
			if (playerPos.xV > tr.p.x) {
				spd->forward();
			}
			else if (playerPos.xV < tr.p.x) {
				spd->backward();
			}
		}
	}

	// Fire every so often

	integrate(t);
}

void Enemy::integrate(float t) {
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

	//cout << vel << " | " << accel << endl;

	// Damping
	//vel *= powf(damping, t);

	// Actualizar posición con velocidad
	tr.p.x += vel.x() * t;
	if (!horizontallyLocked) tr.p.y += vel.y() * t;
	tr.p.z += vel.z() * t;
}

void Enemy::addGen(ForceGenerator* fg) {
	forces.push_back(fg);
}

void Enemy::fire() {
	launcher->emit(1);
}

Vector3D Enemy::getAccel() {
	Vector3D a = { 0,0,0 };
	Vector3D pos = { tr.p.x, tr.p.y, tr.p.z };
	for (auto f : forces) {
		Vector3D force = f->getForce(mass, pos, vel);
		a += force;
	}
	return a;
}