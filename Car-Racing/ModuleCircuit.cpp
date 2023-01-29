#include "Globals.h"
#include "Application.h"
#include "ModuleCircuit.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
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
	Color Water = Blue;	Water.a = 0.1;

	Color Dirt(0.4, 0.2, 0.0);

	// Start
	CreateWallOrFloor(vec3(40, 1, 30), vec3(0, 0, 110));
	
	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3( -30,    0,     100), -45);
	CreateWallOrFloor(vec3(30,   1, 110),  vec3( -40,    0,      35));
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3( -50,    0,     -30), -45);
	CreateWallOrFloor(vec3(20,   1, 30),   vec3( -70,    0,     -40));
	
	// Dirt Part
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3( -90,   -0.25,  -50), -45,  Dirt, ColType::DIRT);
	CreateWallOrFloor(vec3(30,   1, 90),   vec3(-100,   -0.25, -105),   0,  Dirt, ColType::DIRT);
	
	CreateWallOrFloor(vec3(65,   1, 20),   vec3( -82.5, -0.25, -160),   0,  Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(20,   1, 60),   vec3( -60,   -0.25, -120),   0,  Dirt, ColType::DIRT);
	 
	CreateWallOrFloor(vec3(60,   1, 20),   vec3( -40,   -0.25,  -80),   0,  Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(20,   1, 60),   vec3( -20,   -0.25, -120),   0,  Dirt, ColType::DIRT);
	
	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(60,   1, 20),   vec3(   0,   -0.25, -160),   0,  Dirt, ColType::DIRT);
	
	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(20,   1, 60),   vec3(  20,   -0.25, -120),   0,  Dirt, ColType::DIRT);
	
	CreateWallOrFloor(vec3(60,   1, 20),   vec3(  40,   -0.25,  -80),   0,  Dirt, ColType::DIRT);
	
	CreateWallOrFloor(vec3(20,   1, 60),   vec3(  60,   -0.25, -120),   0,  Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(65,   1, 20),   vec3(  82.5, -0.25, -160),   0,  Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(30,   1, 90),   vec3( 100,   -0.25, -105),   0,  Dirt, ColType::DIRT);
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(  90,   -0.25,  -50),  45,  Dirt, ColType::DIRT);

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(  50,    0,     -30), 45);
	CreateWallOrFloor(vec3(20,   1, 30),   vec3(  70,    0,     -40));
	
	// Water ?
	CreateWallOrFloor(vec3(30,   1, 110),  vec3(  40,    0,      35),   0, Water, ColType::WATER);
	
	// x -> minx, y -> minz, z -> maxx, w -> maxz
	DirtArea = vec4(40 - 30 / 2, 35 - 110 / 2, 40 + 30 / 2, 35 + 110 / 2);

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(  30,    0,     100),  45);



	// CheckPoint Flag
	CreateWallOrFloor(vec3(0.3, 15,  0.3), vec3(   0,    0.25, -170));
	CreateWallOrFloor(vec3(0.1,  3,  3),   vec3(   0,    7.5,  -170), 0, Green);

	// WIN SIGN
	CreateWallOrFloor(vec3(0.3, 15,  0.3), vec3(   0,    7.5,   125));
	CreateWallOrFloor(vec3(0.3, 15,  0.3), vec3(   0,    7.5,    95));
	CreateWallOrFloor(vec3(0.1,  5, 30),   vec3(   0,   12.5,   110));
}

// Position is the one of the center of mass (center of the cube)
void ModuleCircuit::CreateWallOrFloor(vec3 size, vec3 pos, float angle, Color color, ColType type)
{
	pos.y += 20;

	// Create rigid body
	btBoxShape* floorshape = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
	btCollisionShape* colShape = floorshape;

	btDefaultMotionState* myMotionState = new btDefaultMotionState();

	btCollisionObject* collider = new btCollisionObject();

	btRigidBody* body = new btRigidBody(0, myMotionState, colShape);

	if (type == ColType::DIRT)
	{
		body->setFriction(btScalar(0.00001));
	}
	else
		body->setFriction(btScalar(10.0));
	
	// Add the rigid to the world
	App->physics->world->addRigidBody(body);
	
	// Add rigid to PhysBody
	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);
	PhysBody->colType = type;

	// Create primitive
	Cube* cube = new Cube(size.x, size.y, size.z);	
	
	cube->SetPos(pos.x, pos.y, pos.z);
	cube->SetRotation(angle, vec3(0,1,0));
	
	// PhysBody Rotation
	PhysBody->SetTransform(cube->transform.M);
	
	cube->color.Set(color.r, color.g, color.b, color.a);

	CubeWallFloorList.add(cube);
}