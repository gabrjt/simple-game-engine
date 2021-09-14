#include "application.h"
#include <flecs.h>
#include <raylib.h>

static ecs_world_t* ecs_world;

void ApplicationInit(const int screen_width, const int screen_height, const char* title, const int target_fps)
{
    InitWindow(screen_width, screen_height, title);
    SetTargetFPS(target_fps);

    ecs_world = ecs_init();
}

ecs_world_t* GetApplicationEcsWorld()
{
    return ecs_world;
}

void ApplicationRun()
{
    while (!WindowShouldClose())
    {
        ecs_progress(ecs_world, GetFrameTime());
    }
}

void ApplicationQuit()
{
    CloseWindow();
    ecs_fini(ecs_world);
}
