#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#include <chrono>
using namespace std;
using namespace chrono;
typedef high_resolution_clock Clock;

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

enum class ShitPostStatus
{
	LOW,
	MEDIUM,
	HIGH,
	UNKNOWN
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	uint Waluigi;
	uint WaluigiLogo;


	uint Gura;
	uint Orcat;

	uint Makima;
	
	uint Wantia;
	uint Wantbro1;
	uint Wantbro2;
	uint Ina;
	uint KawaiiKoto;

	uint sexPau;
	uint Wahmuel;

	uint Goomba;

	uint Bimu;
	uint Rose;
	uint Wairim;
	uint Wakima;
	uint Wabeni;
	
 
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Plane plane;

	steady_clock::time_point level_start;
	steady_clock::time_point level_now;

	long long level_time;
	long long max_time = 60;

	bool bope = false;

	char title[120];

	ShitPostStatus shitpost = ShitPostStatus::MEDIUM;
};
