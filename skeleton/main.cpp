#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Particle.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

vector<Particle*> particles;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	PxShape* sphereShape = CreateShape(PxSphereGeometry(1.0f));

	Vector3D tC = Vector3D(0, 0, 0);
	Vector3D tX = Vector3D(10, 0, 0);
	Vector3D tY = Vector3D(0, 10, 0);
	Vector3D tZ = Vector3D(0, 0, 10);

	PxTransform* sphereTransformC = new PxTransform({ tC.x(), tC.y(), tC.z() });
	PxTransform* sphereTransformX = new PxTransform({ tX.x(), tX.y(), tX.z() });
	PxTransform* sphereTransformY = new PxTransform({ tY.x(), tY.y(), tY.z() });
	PxTransform* sphereTransformZ = new PxTransform({ tZ.x(), tZ.y(), tZ.z() });

	RenderItem* sphereC = new RenderItem(sphereShape, sphereTransformC, { 1,1,1,1 });
	RenderItem* sphereX = new RenderItem(sphereShape, sphereTransformX, { 1,0,0,1 });
	RenderItem* sphereY = new RenderItem(sphereShape, sphereTransformY, { 0,1,0,1 });
	RenderItem* sphereZ = new RenderItem(sphereShape, sphereTransformZ, { 0,0,1,1 });

	Vector3D partP = Vector3D(-20, 0, 0);
	Vector3D partV = Vector3D(20, 100, 0);
	float partM = 10;
	Particle* part = new Particle(partP, partV, partM);
	particles.push_back(part);

	gScene = gPhysics->createScene(sceneDesc);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for (auto p : particles) {
		p->integrate(t);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}