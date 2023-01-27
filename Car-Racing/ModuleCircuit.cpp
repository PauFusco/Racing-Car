#include "Globals.h"
#include "Application.h"
#include "ModuleCircuit.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleCircuit::ModuleCircuit(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleCircuit::~ModuleCircuit()
{}

bool ModuleCircuit::Init()
{
	LOG("Initialising Circuit");

	

	return true;
}

bool ModuleCircuit::Start()
{
	LOG("Loading Circuit");
LoadAllCircuitObjects();
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
	tuputamadre->Render();

	return UPDATE_CONTINUE;
}

void ModuleCircuit::LoadAllCircuitObjects()
{
	// Create rigid body
	btBoxShape* floorshape = new btBoxShape(btVector3(1, 1, 1));
	btCollisionShape* colShape = floorshape;

	btDefaultMotionState* myMotionState = new btDefaultMotionState();

	btRigidBody* body = new btRigidBody(0, myMotionState, colShape);

	// Add the rigid to the world
	App->physics->world->addRigidBody(body);

	// Create PhysBody for the rigid
	floor1xdpb = new PhysBody3D(body);
	
	// Create primitive
	tuputamadre = new Cube(3, 1, 1);

	// Link the PhysBody to the primitive
	floor1xdpb = App->physics->AddBody(*tuputamadre, 0.0);	
}