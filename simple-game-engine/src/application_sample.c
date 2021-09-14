#include "application_sample.h"
#include <flecs.h>
#include "application.h"
#include "component_position.h"
#include "component_screen_clear_background.h"
#include "component_screen_text.h"
#include "system_draw_text.h"
#include "system_screen_clear_background.h"
#include "system_set_screen_text_world_time.h"

void RegisterSampleApplication()
{
    ecs_world_t* ecs_world = GetApplicationECSWorld();

    // Register Components
    ECS_COMPONENT(ecs_world, ComponentPosition);
    ECS_COMPONENT(ecs_world, ComponentScreenClearBackground);
    ECS_COMPONENT(ecs_world, ComponentScreenText);
    ECS_TAG(ecs_world, TagDisplayWorldTime);

    // Register Simulation Systems
    ECS_SYSTEM(ecs_world, SystemSetScreenTextWorldTime, EcsOnUpdate, ComponentScreenText, TagDisplayWorldTime);

    // Register Presentation Systems
    RegisterSystemBeginDrawing();

    ECS_SYSTEM(ecs_world, SystemClearBackground, EcsPostUpdate, ComponentScreenClearBackground);

    ECS_SYSTEM(ecs_world, SystemDrawText, EcsPostUpdate, ComponentScreenText, ComponentPosition);

    RegisterSystemEndDrawing();

    // Create Entities
    const ecs_entity_t entity_screen_clear_background = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_screen_clear_background, ComponentScreenClearBackground, { DARKGRAY });

    const ecs_entity_t entity_congrats_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_congrats_text, ComponentPosition, { GetScreenWidth() * 0.5f - 750, GetScreenHeight() * 0.5f });
    ecs_set(ecs_world, entity_congrats_text, ComponentScreenText, { "Congrats! You created your first window! Powered by raylib", 50, LIGHTGRAY });

    const ecs_entity_t entity_ticking_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_ticking_text, ComponentPosition, { GetScreenWidth() * 0.5f - 200, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_ticking_text, ComponentScreenText, { "flecs is ticking...", 20, LIGHTGRAY });

    const ecs_entity_t entity_display_world_time = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_display_world_time, ComponentPosition, { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_display_world_time, ComponentScreenText, { "", 20, RED });
    ecs_add(ecs_world, entity_display_world_time, TagDisplayWorldTime);
}
