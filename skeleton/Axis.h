#pragma once

#include "Particle.h"
#include "ForceGenerator.h"
#include <vector>

class Axis
{
public:
	Axis(float bR, float bD, float opacity) {
		PxShape* sphereShape = CreateShape(PxSphereGeometry(bR));

		PxTransform* sphereTransformC = new PxTransform({ 0, 0, 0 });
		PxTransform* sphereTransformX = new PxTransform({ bD, 0, 0 });
		PxTransform* sphereTransformY = new PxTransform({ 0, bD, 0 });
		PxTransform* sphereTransformZ = new PxTransform({ 0, 0, bD });
		PxTransform* sphereTransformX2 = new PxTransform({ -bD, 0, 0 });
		PxTransform* sphereTransformY2 = new PxTransform({ 0, -bD, 0 });
		PxTransform* sphereTransformZ2 = new PxTransform({ 0, 0, -bD });

		RenderItem* AxisSphereC = new RenderItem(sphereShape, sphereTransformC, { 1,1,1,opacity });
		RenderItem* AxisSphereX = new RenderItem(sphereShape, sphereTransformX, { 1,0,0,opacity });
		RenderItem* AxisSphereY = new RenderItem(sphereShape, sphereTransformY, { 0,1,0,opacity });
		RenderItem* AxisSphereZ = new RenderItem(sphereShape, sphereTransformZ, { 0,0,1,opacity });
		RenderItem* AxisSphereX2 = new RenderItem(sphereShape, sphereTransformX2, { 0.5,0,0,opacity });
		RenderItem* AxisSphereY2 = new RenderItem(sphereShape, sphereTransformY2, { 0,0.5,0,opacity });
		RenderItem* AxisSphereZ2 = new RenderItem(sphereShape, sphereTransformZ2, { 0,0,0.5,opacity });
	}
};

