#pragma once
#include "Module.h"
#include "Globals.h"
#include "PhysBody3D.h"

struct Cube;

class ModuleCircuit : public Module
{
public:
	ModuleCircuit(Application * app, bool start_enabled = true);
	virtual ~ModuleCircuit();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	void CreateWallOrFloor(vec3 size, vec3 pos, float angle = 0.0,
						   Color color = Color(1, 1, 1, 1),
						   ColType type = ColType::UNKNOWN);
	
	void CreateAllFloors();
	void CreateAllBarriers();

	void CreateDoor1();
	void CreateDoor2();

	void LoadAllCircuitObjects();

	p2List<Cube*> CubeWallFloorList;
	p2List_item<Cube*>* CubeListItem;

	vec4 DirtArea;
	vec4 WaterArea;

	PhysBody3D* PhysBodyA;
	PhysBody3D* PhysBodyB;

	Cube* cubeA;
	Cube* cubeB;

	vec3 posA;
	vec3 posB;


	PhysBody3D* PhysBodyC;
	PhysBody3D* PhysBodyD;

	Cube* cubeC;
	Cube* cubeD;

	vec3 posC;
	vec3 posD;
};