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
	Color Red(1.0, 0.0, 0.0);
	Color Green(0.0, 1.0, 0.0);
	Color Blue(0.0, 0.0, 1.0);
	Color Water = Blue;	Water.a = 0.5;

	Color Dirt(0.4, 0.2, 0.0);

	// Start
	CreateWallOrFloor(vec3(40, 1, 30), vec3(0, 0, 110));
	
	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-30, 0, 100), -45);
	CreateWallOrFloor(vec3(30, 1, 110), vec3(-40, 0, 35));
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-50, 0, -30), -45);
	CreateWallOrFloor(vec3(20, 1, 30), vec3(-70, 0, -40));
	
	// Dirt Part
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-90, -0.25, -50), -45, Dirt);
	CreateWallOrFloor(vec3(30, 1, 90), vec3(-100, -0.25, -105), 0, Dirt);
	
	CreateWallOrFloor(vec3(65, 1, 20), vec3(-82.5, -0.25, -160), 0, Dirt);

	CreateWallOrFloor(vec3(20, 1, 60), vec3(-60, -0.25, -120), 0, Dirt);

	CreateWallOrFloor(vec3(60, 1, 20), vec3(-40, -0.25, -80), 0, Dirt);

	CreateWallOrFloor(vec3(20, 1, 60), vec3(-20, -0.25, -120), 0, Dirt);
	
	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(60, 1, 20), vec3(0, -0.25, -160), 0, Dirt);
	
	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(20, 1, 60), vec3(20, -0.25, -120), 0, Dirt);
	
	CreateWallOrFloor(vec3(60, 1, 20), vec3(40, -0.25, -80), 0, Dirt);
	
	CreateWallOrFloor(vec3(20, 1, 60), vec3(60, -0.25, -120), 0, Dirt);

	CreateWallOrFloor(vec3(65, 1, 20), vec3(82.5, -0.25, -160), 0, Dirt);

	CreateWallOrFloor(vec3(30, 1, 90), vec3(100, -0.25, -105), 0, Dirt);
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(90, -0.25, -50), 45, Dirt);

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(50, 0, -30), 45);
	CreateWallOrFloor(vec3(20, 1, 30), vec3(70, 0, -40));
	
	// Water ?
	CreateWallOrFloor(vec3(30, 1, 110), vec3(40, 0, 35));
	
	//Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(30, 0, 100), 45);
}

// Position is the one of the center of mass (center of the cube)
void ModuleCircuit::CreateWallOrFloor(vec3 size, vec3 pos, float angle, Color color)
{
	// Create rigid body
	btBoxShape* floorshape = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
	btCollisionShape* colShape = floorshape;

	btDefaultMotionState* myMotionState = new btDefaultMotionState();

	btRigidBody* body = new btRigidBody(0, myMotionState, colShape);

	// Add the rigid to the world
	App->physics->world->addRigidBody(body);
	
	// Add rigid to PhysBody
	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);
	
	// Create primitive
	Cube* cube = new Cube(size.x, size.y, size.z);	
	
	cube->SetPos(pos.x, pos.y, pos.z);
	cube->SetRotation(angle, vec3(0,1,0));
	
	// PhysBody Rotation
	PhysBody->SetTransform(cube->transform.M);
	
	cube->color.Set(color.r, color.g, color.b, color.a);

	CubeWallFloorList.add(cube);
}