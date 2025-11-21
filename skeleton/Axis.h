#pragma once

#include "Particle.h"
#include <vector>

class Axis
{
public:
	Axis(float cS, float cD, bool enableLines, float opacity) {

		PxShape* cubeShape = CreateShape(PxBoxGeometry(cS, cS, cS));
		PxTransform* TransformC = new PxTransform({ 0, 0, 0 });
		RenderItem* C = new RenderItem(cubeShape, TransformC, { 1,1,1,opacity });

		if (enableLines) {
			PxShape* XaxisShape = CreateShape(PxBoxGeometry(1000, cS / 3, cS / 3));
			PxShape* YaxisShape = CreateShape(PxBoxGeometry(cS / 3, 1000, cS / 3));
			PxShape* ZaxisShape = CreateShape(PxBoxGeometry(cS / 3, cS / 3, 1000));

			RenderItem* XA = new RenderItem(XaxisShape, TransformC, { 1,0,0,opacity });
			RenderItem* YA = new RenderItem(YaxisShape, TransformC, { 0,1,0,opacity });
			RenderItem* ZA = new RenderItem(ZaxisShape, TransformC, { 0,0,1,opacity });
		}
		else {
			PxTransform* TransformX = new PxTransform({ cD, 0, 0 });
			PxTransform* TransformY = new PxTransform({ 0, cD, 0 });
			PxTransform* TransformZ = new PxTransform({ 0, 0, cD });
			PxTransform* TransformX2 = new PxTransform({ -cD, 0, 0 });
			PxTransform* TransformY2 = new PxTransform({ 0, -cD, 0 });
			PxTransform* TransformZ2 = new PxTransform({ 0, 0, -cD });

			RenderItem* X = new RenderItem(cubeShape, TransformX, { 1,0,0,opacity });
			RenderItem* Y = new RenderItem(cubeShape, TransformY, { 0,1,0,opacity });
			RenderItem* Z = new RenderItem(cubeShape, TransformZ, { 0,0,1,opacity });
			RenderItem* X2 = new RenderItem(cubeShape, TransformX2, { 0.25,0,0,opacity });
			RenderItem* Y2 = new RenderItem(cubeShape, TransformY2, { 0,0.25,0,opacity });
			RenderItem* Z2 = new RenderItem(cubeShape, TransformZ2, { 0,0,0.25,opacity });
		}
	}
};

