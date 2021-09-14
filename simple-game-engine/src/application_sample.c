#include "application_sample.h"
#include <flecs.h>
#include "application.h"
#include "component_screen_clear_background.h"
#include "component_screen_text.h"
#include "component_translation2.h"
#include "system_drawing.h"
#include "system_draw_fps.h"
#include "system_draw_text.h"
#include "system_screen_clear_background.h"
#include "system_set_screen_text_world_time.h"

void RegisterSampleApplication()
{
    ecs_world_t* ecs_world = GetApplicationEcsWorld();

    // Register Components
    ECS_COMPONENT(ecs_world, ComponentTranslation2);
    ECS_COMPONENT(ecs_world, ComponentScreenClearBackground);
    ECS_COMPONENT(ecs_world, ComponentScreenText);
    ECS_TAG(ecs_world, TagSetWorldTime);
    ECS_TAG(ecs_world, TagDrawFps);

    // Register Simulation Systems
    RegisterSystemSetScreenTextWorldTime(ecs_world);

    // Register Presentation Systems
    RegisterSystemBeginDrawing(ecs_world);
    RegisterSystemClearBackground(ecs_world);
    RegisterSystemDrawText(ecs_world);
    RegisterSystemDrawFps(ecs_world);
    RegisterSystemEndDrawing(ecs_world);

    // Create Entities
    const ecs_entity_t entity_screen_clear_background = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_screen_clear_background, ComponentScreenClearBackground, { DARKGRAY });

    const ecs_entity_t entity_congrats_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_congrats_text, ComponentTranslation2, { GetScreenWidth() * 0.5f - 750, GetScreenHeight() * 0.5f });
    ecs_set(ecs_world, entity_congrats_text, ComponentScreenText, { "Congrats! You created your first window! Powered by raylib", 50, LIGHTGRAY });

    const ecs_entity_t entity_ticking_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_ticking_text, ComponentTranslation2, { GetScreenWidth() * 0.5f - 200, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_ticking_text, ComponentScreenText, { "flecs is ticking...", 20, LIGHTGRAY });

    const ecs_entity_t entity_display_world_time = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_display_world_time, ComponentTranslation2, { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_display_world_time, ComponentScreenText, { "", 20, RED });
    ecs_add(ecs_world, entity_display_world_time, TagSetWorldTime);

    const ecs_entity_t entity_display_fps = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_display_fps, ComponentTranslation2, { 10, 10 });
    ecs_add(ecs_world, entity_display_fps, TagDrawFps);
}
