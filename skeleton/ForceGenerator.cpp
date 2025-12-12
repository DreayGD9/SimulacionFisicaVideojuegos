#include "ForceGenerator.h"
#include "mainGame.h"

ForceGenerator::ForceGenerator(string n, FG_TYPE t, bool a, bool areaAffected, Vector3D areaPos, float areaRad) : name(n), type(t), active(a), aA(areaAffected), aP(areaPos), aR(areaRad) {
	if (mainGame::GAME_DEBUG && areaAffected && aR > 0) {
		PxShape* s = CreateShape(PxSphereGeometry(aR));
		PxTransform* sTR = new PxTransform({ aP.xV, aP.yV, aP.zV });
		debugView = new RenderItem(s, sTR, { 1,1,1,0.5 });
		updateDebugView();
	}
	else {
		debugView = nullptr;
	}
};

bool ForceGenerator::isWithinArea(Vector3D pos) {
	if (aA && aR > 0) {
		float dx = pos.xV - aP.xV;
		float dy = pos.yV - aP.yV;
		float dz = pos.zV - aP.zV;

		float dist = sqrt(dx * dx + dy * dy + dz * dz);

		return (dist <= aR);
	}
	else return false;
}

void ForceGenerator::setActive(bool a) { 
	active = a; 
	if (mainGame::GAME_DEBUG) updateDebugView(); 
}

void ForceGenerator::toggleActive() {
	active = !active;
	if (mainGame::GAME_DEBUG) updateDebugView();
}

void ForceGenerator::updateDebugView() {
	if (mainGame::GAME_DEBUG && debugView != nullptr) {
		if (active) debugView->color = { 1,1,1,0.5 };
		else debugView->color = { 1,0,0,0.5 };
		//debugView->actor->getGlobalPose().p.x = aP.xV
	}
}