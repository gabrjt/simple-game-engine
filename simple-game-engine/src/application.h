#pragma once

typedef struct ecs_world_t ecs_world_t;
typedef struct ecs_iter_t ecs_iter_t;

void ApplicationInit(int screen_width, int screen_height, const char* title, int target_fps);

ecs_world_t* GetApplicationEcsWorld();

void ApplicationRun();

void ApplicationQuit();

static void SystemBeginDrawing(const ecs_iter_t* it);

void RegisterSystemBeginDrawing();

static void SystemEndDrawing(const ecs_iter_t* it);

void RegisterSystemEndDrawing();
