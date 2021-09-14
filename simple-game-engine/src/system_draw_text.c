#include "system_draw_text.h"
#include <flecs.h>
#include "component_screen_text.h"
#include "component_translation2.h"

void RegisterSystemDrawText(ecs_world_t* ecs_world)
{
    ECS_SYSTEM(ecs_world, SystemDrawText, EcsPostUpdate, ComponentScreenText, ComponentTranslation2);
}

void SystemDrawText(const ecs_iter_t* it)
{
    const ComponentScreenText* screen_text_components = ecs_term(it, ComponentScreenText, 1);
    const ComponentTranslation2* translation2_components = ecs_term(it, ComponentTranslation2, 2);

    for (int i = 0; i < it->count; i++)
    {
        const ComponentScreenText* screen_text = &screen_text_components[i];
        const ComponentTranslation2* translation2 = &translation2_components[i];

        DrawText(screen_text->text, translation2->value.x, translation2->value.y, screen_text->font_size, screen_text->color);
    }
}
