#include "application.h"
#include <flecs.h>
#include <raylib.h>

static ecs_world_t* ecs_world;

void ApplicationInit(const int screen_width, const int screen_height, const char* title, const int target_fps)
{
    // Init raylib window
    InitWindow(screen_width, screen_height, title);
    SetTargetFPS(target_fps);

    // Init flecs ECS world
    ecs_world = ecs_init();
}

ecs_world_t* GetApplicationECSWorld()
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

void SystemBeginDrawing(const ecs_iter_t* it)
{
    BeginDrawing();
}

void RegisterSystemBeginDrawing()
{
    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = {EcsPostUpdate}
            },
            .callback = SystemBeginDrawing
        }
    );
}

void SystemEndDrawing(const ecs_iter_t* it)
{
    EndDrawing();
}

void RegisterSystemEndDrawing()
{
    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = {EcsPostUpdate}
            },
            .callback = SystemEndDrawing
        }
    );
}
