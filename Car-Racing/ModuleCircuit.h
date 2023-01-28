#pragma once
#include "Module.h"
#include "Globals.h"

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
	void CreateWallOrFloor(vec3 size, vec3 pos, float angle = 0.0, Color color = Color(1,1,1,1));
	void LoadAllCircuitObjects();

	p2List<Cube*> CubeWallFloorList;
	p2List_item<Cube*>* CubeListItem;
};