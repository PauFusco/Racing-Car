#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "glut/glut.h"

#define MAX_LIGHTS 8

enum class TextureOrientation
{
	X,
	Y,
	Z,
	UNKNOWN
};

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	uint LoadTexture(const char* path);
	void UnloadTexture(uint id);

	void DrawTexture(uint texture, vec3 pos, float size, TextureOrientation orientation);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	TextureOrientation orientation;
};