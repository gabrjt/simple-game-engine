#include "system_drawing.h"
#include <flecs.h>
#include <raylib.h>

void RegisterSystemBeginDrawing(ecs_world_t* ecs_world)
{
    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = { EcsPostUpdate }
            },
            .callback = SystemBeginDrawing
        }
    );
}

void SystemBeginDrawing(const ecs_iter_t* it)
{
    BeginDrawing();
}

void RegisterSystemEndDrawing(ecs_world_t* ecs_world)
{
    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = { EcsPostUpdate }
            },
            .callback = SystemEndDrawing
        }
    );
}

void SystemEndDrawing(const ecs_iter_t* it)
{
    EndDrawing();
}
