#pragma once
#include "Module.h"
#include "Globals.h"

struct Cube;

class ModuleCircuit : public Module
{
public:
	ModuleCircuit(Application * app, bool start_enabled = true);
	virtual ~ModuleCircuit();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	void LoadAllCircuitObjects();

public:
	PhysBody3D* floor1xdpb;
	Cube* tuputamadre;

};