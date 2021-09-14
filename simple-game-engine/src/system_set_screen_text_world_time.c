#include "system_set_screen_text_world_time.h"
#include <flecs.h>
#include "component_screen_text.h"

void RegisterSystemSetScreenTextWorldTime(ecs_world_t* ecs_world)
{
    ECS_SYSTEM(ecs_world, SystemSetScreenTextWorldTime, EcsOnUpdate, ComponentScreenText, TagSetWorldTime);
}

void SystemSetScreenTextWorldTime(const ecs_iter_t* it)
{
    ComponentScreenText* screen_text_components = ecs_term(it, ComponentScreenText, 1);

    for (int i = 0; i < it->count; i++)
    {
        sprintf_s(screen_text_components[i].text, COMPONENT_SCREEN_TEXT_BUFFER_SIZE, "%f", it->world_time);
    }
}
