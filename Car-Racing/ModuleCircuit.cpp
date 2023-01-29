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

	// Render Circuit
	while (CubeListItem != NULL)
	{
		CubeListItem->data->Render();
		CubeListItem = CubeListItem->next;
	}

	PhysBodyA->GetTransform(cubeA->transform.M);
	//PhysBodyB->GetTransform(cubeB->transform.M);

	cubeA->Render();
	//cubeB->Render();


	//PhysBodyC->GetTransform(cubeC->transform.M);
	PhysBodyD->GetTransform(cubeD->transform.M);

	//cubeC->Render();
	cubeD->Render();

	return UPDATE_CONTINUE;
}

void ModuleCircuit::LoadAllCircuitObjects()
{
	
	CreateAllFloors();

	// CheckPoint Flag
	CreateWallOrFloor(vec3(0.3,  7.5,  0.3), vec3( 0,    7.75, -170));
	CreateWallOrFloor(vec3(0.1,  3,  3),   vec3(   0,    10,  -170), 0, Green);

	// WIN SIGN
	CreateWallOrFloor(vec3(0.3, 15,  0.3), vec3(   0,    7.5,   125));
	CreateWallOrFloor(vec3(0.3, 15,  0.3), vec3(   0,    7.5,    95));
	CreateWallOrFloor(vec3(0.1,  5, 30),   vec3(   0,   12.5,   110));

	CreateAllBarriers();

	CreateDoor1();
	CreateDoor2();
}

void ModuleCircuit::CreateAllFloors()
{
	// Colors
	Color Red(1.0, 0.0, 0.0);
	Color Green(0.0, 1.0, 0.0);
	Color Blue(0.0, 0.0, 1.0);
	Color Water = Blue;
	Color Dirt(0.4, 0.2, 0.0);

	// Start
	CreateWallOrFloor(vec3(40, 1, 30), vec3(0, 0, 110));

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-30, 0, 100), -45);
	CreateWallOrFloor(vec3(30, 1, 110), vec3(-40, 0, 35));
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-50, 0, -30), -45);
	CreateWallOrFloor(vec3(20, 1, 30), vec3(-70, 0, -40));

	// Dirt Part
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(-90, -0.25, -50), -45, Dirt, ColType::DIRT);
	CreateWallOrFloor(vec3(30, 1, 90), vec3(-100, -0.25, -105), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(65, 1, 20), vec3(-82.5, -0.25, -160), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(20, 1, 60), vec3(-60, -0.25, -120), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(60, 1, 20), vec3(-40, -0.25, -80), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(20, 1, 60), vec3(-20, -0.25, -120), 0, Dirt, ColType::DIRT);

	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(60, 1, 20), vec3(0, -0.25, -160), 0, Dirt, ColType::DIRT);

	// ---------------------------------------------------------------- //

	CreateWallOrFloor(vec3(20, 1, 60), vec3(20, -0.25, -120), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(60, 1, 20), vec3(40, -0.25, -80), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(20, 1, 60), vec3(60, -0.25, -120), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(65, 1, 20), vec3(82.5, -0.25, -160), 0, Dirt, ColType::DIRT);

	CreateWallOrFloor(vec3(30, 1, 90), vec3(100, -0.25, -105), 0, Dirt, ColType::DIRT);
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(90, -0.25, -50), 45, Dirt, ColType::DIRT);

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(50, 0, -30), 45);
	CreateWallOrFloor(vec3(20, 1, 30), vec3(70, 0, -40));

	// Water ?
	CreateWallOrFloor(vec3(30, 1, 110), vec3(40, 0, 35), 0, Water, ColType::WATER);

	// x -> minx, y -> minz, z -> maxx, w -> maxz
	WaterArea = vec4(40 - 30 / 2, 35 - 110 / 2, 40 + 30 / 2, 35 + 110 / 2);

	// Normal
	CreateWallOrFloor(vec3(49.5, 1, 21.2), vec3(30, 0, 100), 45);
}

void ModuleCircuit::CreateAllBarriers()
{			
	float size1 = 1.25, size2 = 1;
	CreateWallOrFloor(vec3( 40,   1, 1), vec3(   0,   size1, 125));
	CreateWallOrFloor(vec3( 40,   1, 1), vec3(   0,   size1,  95));
							     
	CreateWallOrFloor(vec3( 50,   1, 1), vec3( -37.5, size1, 108),   -45);
	CreateWallOrFloor(vec3(  7,   1, 1), vec3( -22.5, size1,  92.5), -45);
							     
	CreateWallOrFloor(vec3(110,   1, 1), vec3( -55,   size1,  35), 90);
	CreateWallOrFloor(vec3(110,   1, 1), vec3( -25,   size1,  35), 90);
							     
	CreateWallOrFloor(vec3( 50,   1, 1), vec3( -42.5, size1, -38), -45);
	CreateWallOrFloor(vec3(  7,   1, 1), vec3( -57.5, size1, -22), -45);

	CreateWallOrFloor(vec3( 20,   1, 1), vec3( -70,   size1, -25));
	CreateWallOrFloor(vec3( 20,   1, 1), vec3( -70,   size1, -55));

	//
	//
	
	CreateWallOrFloor(vec3(107.5, 1, 1), vec3(-115,   size2, -115), 90);
	CreateWallOrFloor(vec3( 90,   1, 1), vec3( -85,   size2, -105), 90);
						    						 
	CreateWallOrFloor(vec3( 15,   1, 1), vec3( -77.5, size2, -150));
	CreateWallOrFloor(vec3( 65,   1, 1), vec3( -82.5, size2, -170));
							     					  
	CreateWallOrFloor(vec3( 80,   1, 1), vec3( -50,   size2, -130), 90);
	CreateWallOrFloor(vec3( 80,   1, 1), vec3( -70,   size2, -110), 90);
							     					  
	CreateWallOrFloor(vec3( 60,   1, 1), vec3( -40,   size2,  -70));
	CreateWallOrFloor(vec3( 20,   1, 1), vec3( -40,   size2,  -90));
							     					  
	CreateWallOrFloor(vec3( 80,   1, 1), vec3( -30,   size2, -130), 90);
	CreateWallOrFloor(vec3( 80,   1, 1), vec3( -10,   size2, -110), 90);



	CreateWallOrFloor(vec3(20, 1, 1), vec3(0, 0.75, -150));
	CreateWallOrFloor(vec3(60, 1, 1), vec3(0, 0.75, -170));



	CreateWallOrFloor(vec3(80,    1, 1), vec3(30,   size2, -130), 90);
	CreateWallOrFloor(vec3(80,    1, 1), vec3(10,   size2, -110), 90);

	CreateWallOrFloor(vec3(60,    1, 1), vec3(40,   size2,  -70));
	CreateWallOrFloor(vec3(20,    1, 1), vec3(40,   size2,  -90));
							      
	CreateWallOrFloor(vec3(80,    1, 1), vec3(50,   size2, -130), 90);
	CreateWallOrFloor(vec3(80,    1, 1), vec3(70,   size2, -110), 90);
							      
	CreateWallOrFloor(vec3(15,    1, 1), vec3(77.5, size2, -150));
	CreateWallOrFloor(vec3(65,    1, 1), vec3(82.5, size2, -170));

	CreateWallOrFloor(vec3(107.5, 1, 1), vec3(115,  size2, -115), 90);
	CreateWallOrFloor(vec3(90,    1, 1), vec3( 85,  size2, -105), 90);

	//
	//

	CreateWallOrFloor(vec3(20, 1, 1), vec3(70, 1, -25));
	CreateWallOrFloor(vec3(20, 1, 1), vec3(70, 1, -55));

	CreateWallOrFloor(vec3(50, 1, 1), vec3(42.5, 1, -38),45);
	CreateWallOrFloor(vec3(7, 1, 1), vec3(57.5, 1, -22), 45);

	CreateWallOrFloor(vec3(110, 1, 1), vec3(55, 1, 35), 90);
	CreateWallOrFloor(vec3(110, 1, 1), vec3(25, 1, 35), 90);

	CreateWallOrFloor(vec3(50, 1, 1), vec3(37.5, 1, 108), 45);
	CreateWallOrFloor(vec3(7, 1, 1), vec3(22.5, 1, 92.5), 45);

}

void ModuleCircuit::CreateDoor1()
{
	vec3 size, posA, posB;
	size = vec3(10, 11, 1);
	posA = vec3(-32, 26, 30);
	posB = vec3(-25, 26, 30);
	float angle = 0;

	// Create primitive
	cubeA = new Cube(size.x, size.y, size.z);
	cubeB = new Cube(size.x / 2, size.y, size.z);

	cubeA->SetPos(posA.x, posA.y, posA.z);
	cubeA->SetRotation(angle, vec3(0, 1, 0));

	cubeB->SetPos(posB.x, posB.y, posB.z);
	cubeB->SetRotation(angle, vec3(0, 1, 0));

	PhysBodyA = App->physics->AddBody(*cubeA, 100);
	PhysBodyB = App->physics->AddBody(*cubeB, 0);

	App->physics->AddConstraintHinge(*PhysBodyA, *PhysBodyB, vec3(5,0,0), vec3(-4,0,0), vec3(0,1,0), vec3(0,-1,0), true);
}

void ModuleCircuit::CreateDoor2()
{
	vec3 size, posA, posB;
	size = vec3(10, 11, 1);
	posA = vec3(-52, 26, 30);
	posB = vec3(-45, 26, 30);
	float angle = 0;

	// Create primitive
	cubeC = new Cube(size.x / 2, size.y, size.z);
	cubeD = new Cube(size.x, size.y, size.z);

	cubeC->SetPos(posA.x, posA.y, posA.z);
	cubeC->SetRotation(angle, vec3(0, 1, 0));

	cubeD->SetPos(posB.x, posB.y, posB.z);
	cubeD->SetRotation(angle, vec3(0, 1, 0));

	PhysBodyC = App->physics->AddBody(*cubeC, 0);
	PhysBodyD = App->physics->AddBody(*cubeD, 100);

	App->physics->AddConstraintHinge(*PhysBodyD, *PhysBodyC, vec3(-4, 0, 0), vec3(4, 0, 0), vec3(0, 1, 0), vec3(0, -1, 0), true);
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

	
	// Add the rigid to the world
	App->physics->world->addRigidBody(body);
	
	// Add rigid to PhysBody
	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);
	PhysBody->colType = type;

	// Create primitive
	Cube* cube = new Cube(size.x, size.y, size.z);	
	
	cube->SetPos(pos.x, pos.y, pos.z);
	cube->SetRotation(angle, vec3(0, 1, 0));
	
	// PhysBody Rotation
	PhysBody->SetTransform(cube->transform.M);
	
	cube->color.Set(color.r, color.g, color.b, color.a);

	CubeWallFloorList.add(cube);
}

