#include "system_screen_clear_background.h"
#include <flecs.h>
#include "component_screen_clear_background.h"

void RegisterSystemClearBackground(ecs_world_t* ecs_world)
{
    ECS_SYSTEM(ecs_world, SystemClearBackground, EcsPostUpdate, ComponentScreenClearBackground);
}

void SystemClearBackground(const ecs_iter_t* it)
{
    const ComponentScreenClearBackground* screen_clear_background_components = ecs_term(it, ComponentScreenClearBackground, 1);

    for (int i = 0; i < it->count; i++)
    {
        ClearBackground(screen_clear_background_components[i].value);
    }
}
