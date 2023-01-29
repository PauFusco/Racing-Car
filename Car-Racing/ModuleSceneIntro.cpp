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

	//texRandom = App->renderer3D->LoadTexture("Wahssets/Images/gurrra.jpg");

	Waluigi = App->renderer3D->LoadTexture("Wahssets/Images/sex2.jpg");
	WaluigiLogo = App->renderer3D->LoadTexture("Wahssets/Images/wahlogo.jpg");
	Gura = App->renderer3D->LoadTexture("Wahssets/Images/Wah.jpg");
	Orcat = App->renderer3D->LoadTexture("Wahssets/Images/Lily.jpg");
	Makima = App->renderer3D->LoadTexture("Wahssets/Images/Makima.jpg");
	Wantia = App->renderer3D->LoadTexture("Wahssets/Images/wantia.jpg");
	Wantbro1 = App->renderer3D->LoadTexture("Wahssets/Images/wantia.jpg");
	Wantbro2 = App->renderer3D->LoadTexture("Wahssets/Images/wantia.jpg");
	Ina = App->renderer3D->LoadTexture("Wahssets/Images/Ina.jpg");
	KawaiiKoto = App->renderer3D->LoadTexture("Wahssets/Images/Kawaii.jpg");

	//sexPau = App->renderer3D->LoadTexture("Wahssets/Images/Sex.jpg");
	//Wahmuel = App->renderer3D->LoadTexture("Wahssets/Images/Wahmuel.jpg");
	//Goomba = App->renderer3D->LoadTexture("Wahssets/Images/Goomba.jpg");
	//Rose = App->renderer3D->LoadTexture("Wahssets/Images/Rose.jpg");
	//Wairim = App->renderer3D->LoadTexture("Wahssets/Images/Wairim.jpg");
	//Wabeni = App->renderer3D->LoadTexture("Wahssets/Images/Wabeni.jpg");
	//Wakima = App->renderer3D->LoadTexture("Wahssets/Images/wakima.jpg");
	//Bimu = App->renderer3D->LoadTexture("Wahssets/Images/Bimu.jpg");

	
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
		sprintf_s(title, "If you fall a portal will teleport you to the start, don't worry! You have %d seconds left! (Beware the allmighty dirt)", int(max_time - level_time));
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

	//App->renderer3D->DrawTexture(texRandom, vec3(0, 20.6, 120), 100, TextureOrientation::Z);

	switch (shitpost) {
	case ShitPostStatus::LOW:



		break;

	case ShitPostStatus::MEDIUM:


		break;

	case ShitPostStatus::HIGH:



		break;
	}

	App->renderer3D->DrawTexture(Waluigi, vec3(13, 20, 83), 50, TextureOrientation::Z);
	App->renderer3D->DrawTexture(WaluigiLogo, vec3(13, 20, -32), 50, TextureOrientation::Z);

	App->renderer3D->DrawTexture(Gura, vec3(25, 17, 89.5), 30, TextureOrientation::Y);
	App->renderer3D->DrawTexture(Orcat, vec3(25, 15, -20.5), 30, TextureOrientation::Y);


	App->renderer3D->DrawTexture(Makima, vec3(-500, 0, -500), 1000, TextureOrientation::Z);
	App->renderer3D->DrawTexture(Wantia, vec3(-10, 17, -150), 20, TextureOrientation::Y);
	App->renderer3D->DrawTexture(Wantia, vec3(70, 17, -150), 15, TextureOrientation::Y);
	App->renderer3D->DrawTexture(Wantia, vec3(-85, 17, -150), 15, TextureOrientation::Y);
	App->renderer3D->DrawTexture(Ina, vec3(-70, 17, -70), 55, TextureOrientation::Y);
	App->renderer3D->DrawTexture(KawaiiKoto, vec3(10, 17, -70), 55, TextureOrientation::Y);


	//app->renderer3d->drawtexture(waluigi, vec3(13, 20, 83), 50, textureorientation::z);
	//app->renderer3d->drawtexture(waluigilogo, vec3(13, 20, -32), 50, textureorientation::z);

	//app->renderer3d->drawtexture(sexpau, vec3(25, 17, 89.5), 30, textureorientation::y);
	//app->renderer3d->drawtexture(wahmuel, vec3(25, 15, -20.5), 30, textureorientation::y);


	//app->renderer3d->drawtexture(goomba, vec3(-500, 0, -500), 1000, textureorientation::z);
	//app->renderer3d->drawtexture(rose, vec3(-10, 17, -150), 20, textureorientation::y);
	//app->renderer3d->drawtexture(wakima, vec3(70, 17, -150), 15, textureorientation::y);
	//app->renderer3d->drawtexture(wabeni, vec3(-85, 17, -150), 15, textureorientation::y);
	//app->renderer3d->drawtexture(bimu, vec3(-70, 17, -70), 55, textureorientation::y);
	//app->renderer3d->drawtexture(wairim, vec3(10, 17, -70), 55, textureorientation::y);






	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{ 
}

