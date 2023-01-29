#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	
	Plane p(0, 1, 0, 0);
	plane = p;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//App->audio->PlayMusic("Wahssets/Audio/Waluigi_theme_eurobeat.wav");

	level_start = Clock::now();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	level_now = Clock::now();

	level_time = duration_cast<seconds>(level_now - level_start).count();

	if (!App->player->Win) {
		sprintf_s(title, "If you fall a portal will teleport you to the start, don't worry! You have %d seconds left!", int(max_time - level_time));
		App->window->SetTitle(title);
	}
	else
	{
		sprintf_s(title, "YOU WIN!!¡!!1¡!!11¡!1! (Reset in %d seconds)", int(max_time - level_time));
		App->window->SetTitle(title);
	}

	if (level_time >= max_time)
	{
		App->player->Reset();
	}

	if(App->physics->debug)
	{
		plane.axis = true;
		plane.Render();
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

