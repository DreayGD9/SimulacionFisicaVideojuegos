#include "Enemy.h"
#include "Player.h"
#include "FG_Library.h"
#include "mainGame.h"

Enemy::Enemy(Vector3D p, float m, float ms, PxShape* s, Vector4 c, float d, float pow, Player* pl, mainGame* g) : Particle(p, { 0,0,0 }, m, 1, nullptr, s, c), maxSpd(ms), player(pl), horizontallyLocked(true), shotDelay(d), shotPower(pow), game(g) {
	int nParticles = 500;
	Vector3D pos = { 0,0,0 };
	Vector3D dir = { 0,0,0 };
	Vector3D ang = { 0,0,0 };
	Vector3D posR = { 0,0,0 };
	Vector3D dirR = { 5,5,5 };
	Vector3D angR = { 5,5,5 };
	float lifetime = 5;
	float lifetimeR = 1;
	float mass = 10;
	PxShape* partShape = CreateShape(PxBoxGeometry(1, 1, 1), game->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f));
	Vector4 colour = { 1,1,1,1 };
	launcher = new ObjectSystem(nParticles, pos, dir, ang, posR, dirR, angR, shotDelay, lifetime, lifetimeR, mass, partShape, colour, game);
	/*
	int n,
		Vector3D sP,
		Vector3D sD,
		Vector3D sA,
		Vector3D pR,
		Vector3D dR,
		Vector3D aR,
		float spD,
		float sT,
		float rT,
		float pM,
		PxShape* s,
		Vector4 c,
		mainGame* g
	*/
	launcher->enable(false);
}

void Enemy::update(float t) {


	Vector3D playerPos = player->returnPos();
	Vector3D selfPos = { tr.p.x, tr.p.y, tr.p.z };

	// Place the launcher on the enemy's position then aim at the player

	launcher->update(t);
	launcher->updatePos(selfPos);

	Vector3D aimDir = Vector3D(playerPos - selfPos).normalize();
	Vector3D aim = { aimDir.xV * shotPower, shotPower / 20, aimDir.zV * shotPower };

	launcher->updateDir(aim);


	// Attempt matching X axis position of player and move towards it

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
void Enemy::addGenToShots(ForceGenerator* fg) {
	launcher->addGen(fg);
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