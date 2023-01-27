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

	PhysBody3D* floor1xdb;
	Primitive* tuputamadre;

};