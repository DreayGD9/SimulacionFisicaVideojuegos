#include "ForceGenerator.h"
#include "mainGame.h"

ForceGenerator::ForceGenerator(string n, bool areaAffected, Vector3D areaPos, float areaRad) : name(n), aA(areaAffected), aP(areaPos), aR(areaRad) {
	if (mainGame::GAME_DEBUG && areaAffected && aR > 0) {
		PxShape* s = CreateShape(PxSphereGeometry(aR));
		PxTransform* sTR = new PxTransform({ aP.xV, aP.yV, aP.zV });
		RenderItem* AxisSphereC = new RenderItem(s, sTR, { 1,1,1,0.5 });
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