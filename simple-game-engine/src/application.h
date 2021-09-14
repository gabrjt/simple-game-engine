#pragma once

typedef struct ecs_world_t ecs_world_t;

void ApplicationInit(int screen_width, int screen_height, const char* title, int target_fps);

ecs_world_t* GetApplicationEcsWorld();

void ApplicationRun();

void ApplicationQuit();
