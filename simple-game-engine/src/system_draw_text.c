#include "system_draw_text.h"
#include <flecs.h>
#include "component_position.h"
#include "component_screen_text.h"

void SystemDrawText(const ecs_iter_t* it)
{
    const ComponentScreenText* screen_text_components = ecs_term(it, ComponentScreenText, 1);
    const ComponentPosition*   position_components    = ecs_term(it, ComponentPosition, 2);

    for (int i = 0; i < it->count; i++)
    {
        const ComponentScreenText* screen_text = &screen_text_components[i];
        const ComponentPosition*   position    = &position_components[i];

        DrawText(screen_text->text, position->x, position->y, screen_text->font_size, screen_text->color);
    }
}
