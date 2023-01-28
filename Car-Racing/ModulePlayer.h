#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	btVector3 CarPos();
	vec2 CarRot();

	bool CheckDirt();

	void Debug();

public:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	btRigidBody* vehiclerb;

	vec4 Darea;

	float massSetter;

	float GravityX;
	float GravityY;
	float GravityZ;
};