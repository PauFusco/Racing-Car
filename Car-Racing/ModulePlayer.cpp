#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

#include <chrono>
using namespace std;
using namespace chrono;
typedef high_resolution_clock Clock;

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 20.0;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);

	startPos = vec3(0, 22, 110);

	vehicle->SetPos(startPos.x, startPos.y, startPos.z);
	//vehicle->SetTransform();

	Warea = App->circuit->WaterArea;
	btVector3 originalGravity = App->physics->world->getGravity();

	GravityX = originalGravity.x();
	GravityY = originalGravity.y();
	GravityZ = originalGravity.z();

	vehiclerb = vehicle->vehicle->getRigidBody();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

btVector3 ModulePlayer::CarPos()
{
	btVector3 aaa = vehicle->vehicle->getChassisWorldTransform().getOrigin();
	return aaa;
}

vec2 ModulePlayer::CarRot()
{
	vec2 cPos;

	//vehicle->vehicle->getChassisWorldTransform().getRotation().

	btQuaternion q = vehicle->vehicle->getChassisWorldTransform().getRotation();

	q.normalize();

	double sinp = (1 + 2 * (q.getW() * q.getY() - q.getX() * q.getZ()));
	double cosp = (1 - 2 * (q.getW() * q.getY() - q.getX() * q.getZ()));
	sinp = sinp / cosp;
	sinp = sqrt(sinp);
	float rot = 2 * atan(sinp) - M_PI / 2;

	//double sinp = 2 * (q.getW() * q.getZ() + q.getX() * q.getY());
	//double cosp = 1 - 2 * (q.getY() * q.getY() + q.getZ() * q.getZ());
	//sinp = sinp / cosp;
	//float rot = atan(sinp);



	cPos.x = cos(rot);
	cPos.y = sin(rot);

	//cPos.x = vehicle->vehicle->getWheelInfo(3).m_wheelDirectionCS.y();
	//cPos.y = sin(vehicle->vehicle->getChassisWorldTransform().getRotation().getY());

	return cPos;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	Movement();

	

	if (vehicle->GetPos().y <= 10)
	{
		Reset();
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		vehicle->SetPos(0.0, 20.25, -160);
	}

	if (vehicle->GetPos().z < -150)
	{
		if (0.1 > vehicle->GetPos().x > -0.1)
		{
			CheckPoint = true;
		}
	}

	if (CheckPoint)
	{
		if (vehicle->GetPos().z > 95)
		{
			if (0.1 > vehicle->GetPos().x > -0.1)
			{
				Win = true;
			}
		}
	}

	if (vehicle->GetPos().z < -80) {
		vehicle->vehicle->m_wheelInfo[0].m_frictionSlip = 2.0;
		vehicle->vehicle->m_wheelInfo[1].m_frictionSlip = 2.0;
		vehicle->vehicle->m_wheelInfo[2].m_frictionSlip = 2.0;
		vehicle->vehicle->m_wheelInfo[3].m_frictionSlip = 2.0;
	}
	else {
		vehicle->vehicle->m_wheelInfo[0].m_frictionSlip = 20.0;
		vehicle->vehicle->m_wheelInfo[1].m_frictionSlip = 20.0;
		vehicle->vehicle->m_wheelInfo[2].m_frictionSlip = 20.0;
		vehicle->vehicle->m_wheelInfo[3].m_frictionSlip = 20.0;
	}

	if (CheckWater())
	{
		vehicle->vehicle->m_wheelInfo[0].m_frictionSlip = 1.0;
		vehicle->vehicle->m_wheelInfo[1].m_frictionSlip = 1.0;
		vehicle->vehicle->m_wheelInfo[2].m_frictionSlip = 1.0;
		vehicle->vehicle->m_wheelInfo[3].m_frictionSlip = 1.0;

		if (vehicle->GetKmh() < 10)
		{
			BouMov();
		}
	}
	
	
	Debug();
	
	vehicle->Render();

	return UPDATE_CONTINUE;
}

void ModulePlayer::Movement()
{
	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT)
	{
		vehicle->Push(0, 200, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT)
	{
		vehicle->Push(10, 100, 0);
	}
}

bool ModulePlayer::CheckDirt()
{
	bool ret = false;
	
	vec3 VPos = vehicle->GetPos();

	// x -> minx, y -> minz, z -> maxx, w -> maxz
	float minX = Darea.x, minZ = Darea.y, maxX = Darea.z, maxZ = Darea.w;


	if (minX < VPos.x)
	{
		if (VPos.x < maxX)
		{
			if (minZ < VPos.z)
			{
				if (VPos.z < maxZ)
				{
					ret = true;
				}
			}	
		}
	}

	return ret;
}

bool ModulePlayer::CheckWater()
{
	bool ret = false;

	vec3 VPos = vehicle->GetPos();

	// x -> minx, y -> minz, z -> maxx, w -> maxz
	float minX = Warea.x, minZ = Warea.y, maxX = Warea.z, maxZ = Warea.w;


	if (minX < VPos.x)
	{
		if (VPos.x < maxX)
		{
			if (minZ < VPos.z)
			{
				if (VPos.z < maxZ)
				{
					ret = true;
				}
			}
		}
	}

	return ret;
}

void ModulePlayer::BouMov()
{
	//if (App->input->GetKey(SDL_SCANCODE_V) == KEY_REPEAT)
	{
		btVector3 aaa = vehicle->vehicle->getChassisWorldTransform().getOrigin();


		//LOG("the axis is this: %f", aaa.z());

		if (aaa.z() > 25 && aaa.y() - 1 < 10) //here you have to define the water area, the -1 is there to make it calculate the bottom of the car, 10 is the surface, you can change it
		{
			float Fb, Fd;

			float Vol;
			Vol = (25 - aaa.y() - 1) - (25 - aaa.y() + 1);
			if ((25 - aaa.y() + 1) > 25)
			{
				Vol = (25 - aaa.y() - 1);
			}

			float density;

			density = 10;

			Fb = (density * GRAVITY.y() * Vol) * 0.6;

			if (vehicle->GetKmh() > 10) // this is not a perfect way of doing it but it is the best that i've been able to do so far
			{
				Fd = 99 * vehicle->GetKmh() / 3.6;   // the value on the left can be modified

				vehicle->ApplyEngineForce(-Fd / vehicle->info.mass);
			}

			vehicle->Push(0, Fb, 0);
		}

	}
}

void ModulePlayer::Debug()
{
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
	{
		vehicle->info.mass += 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		vehicle->info.mass -= 10;
	}

	vehiclerb->setMassProps(vehicle->info.mass, vehiclerb->getLocalInertia());


	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		GravityX += 0.5;
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		GravityX -= 0.5;
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		GravityY += 0.5;
	}
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		GravityY -= 0.5;
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		GravityZ += 0.5;
	}
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		GravityZ -= 0.5;
	}

	App->physics->world->setGravity(btVector3(GravityX, GravityY, GravityZ));


	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_REPEAT)
	{
		vehicle->setGrav({ 0,0,0 });
	}
	else
	{
		vehicle->setGrav({ GravityX,GravityY,GravityZ });
	}
}

void ModulePlayer::SetVehiclePos(vec3 pos)
{
	vehicle->SetPos(pos.x, pos.y, pos.z);
}

void ModulePlayer::Reset()
{
	vehicle->SetAngularVelocity(0, 0, 0);
	SetVehiclePos(startPos);

	CheckPoint = false, Win = false;

	App->scene_intro->level_start = Clock::now();
}