#include "Globals.h"
#include "Application.h"
#include "ModuleCircuit.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModuleCircuit::ModuleCircuit(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleCircuit::~ModuleCircuit()
{}

bool ModuleCircuit::Start()
{
	LOG("Loading Circuit");


	btBoxShape* floorshape = new btBoxShape(btVector3(1, 1, 1));
	btCollisionShape* colShape = floorshape;
	
	btDefaultMotionState* myMotionState = new btDefaultMotionState();
	
	btRigidBody* body = new btRigidBody(0, myMotionState, colShape);
	
	floor1xdb = new PhysBody3D(body);

	

	return true;
}

// Unload assets
bool ModuleCircuit::CleanUp()
{
	LOG("Unloading circuit");

	return true;
}

// Update: draw background
update_status ModuleCircuit::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}