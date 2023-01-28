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
	CubeListItem = CubeWallFloorList.getFirst();

	while (CubeListItem != NULL)
	{
		CubeListItem->data->Render();
		CubeListItem = CubeListItem->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleCircuit::LoadAllCircuitObjects()
{
	CreateWallOrFloor(vec3(50, 1, 50), vec3(1, 1, 1));
	CreateWallOrFloor(vec3(50, 1, 50), vec3(1, 1, 51));
}

// Position is the one of the center of mass (center of the cube)
void ModuleCircuit::CreateWallOrFloor(vec3 size, vec3 pos)
{
	// Create rigid body
	btBoxShape* floorshape = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
	btCollisionShape* colShape = floorshape;

	btDefaultMotionState* myMotionState = new btDefaultMotionState();

	btRigidBody* body = new btRigidBody(0, myMotionState, colShape);

	// Add the rigid to the world
	App->physics->world->addRigidBody(body);
	
	// Add rigid to physbody
	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);

	// Create primitive
	Cube* cube = new Cube(size.x, size.y, size.z);	
	
	cube->SetPos(pos.x, pos.y, pos.z);

	CubeWallFloorList.add(cube);
}