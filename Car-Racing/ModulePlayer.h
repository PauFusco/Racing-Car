#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define WATER_ACCELERATION  500.0f
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

	void Movement();

	bool CheckDirt();
	bool CheckWater();

	void BouMov();

	void Debug();

	void SetVehiclePos(vec3 pos);
	void Reset();

public:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	btRigidBody* vehiclerb;

	vec4 Darea;
	vec4 Warea;

	float massSetter;

	float GravityX;
	float GravityY;
	float GravityZ;

	vec3 startPos;

	bool CheckPoint = false;
	bool Win = false;
};