#include "system_draw_fps.h"
#include <flecs.h>
#include <raylib.h>
#include "component_translation2.h"

void RegisterSystemDrawFps(ecs_world_t* ecs_world)
{
    ECS_SYSTEM(ecs_world, SystemDrawFps, EcsPostUpdate, ComponentTranslation2, TagDrawFps);
}

void SystemDrawFps(const ecs_iter_t* it)
{
    const ComponentTranslation2* translation2_components = ecs_term(it, ComponentTranslation2, 1);

    for (int i = 0; i < it->count; i++)
    {
        const ComponentTranslation2* translation2 = &translation2_components[i];

        DrawFPS(translation2->value.x, translation2->value.y);
    }
}
