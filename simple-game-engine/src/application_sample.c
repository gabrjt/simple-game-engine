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

#define REGISTER_COMPONENTS(ecs_world) \
    ECS_COMPONENT(ecs_world, ComponentTranslation2); \
    ECS_COMPONENT(ecs_world, ComponentScreenClearBackground); \
    ECS_COMPONENT(ecs_world, ComponentScreenText); \
    ECS_TAG(ecs_world, TagSetWorldTime); \
    ECS_TAG(ecs_world, TagDrawFps);

#define CREATE_ENTITY_CLEAR_BACKGROUND(ecs_world, entity, ...) \
    const ecs_entity_t entity = ecs_new_id(ecs_world); \
    ecs_set(ecs_world, entity, ComponentScreenClearBackground, { __VA_ARGS__ });

#define CREATE_ENTITY_TEXT(ecs_world, entity, x, y, text, font_size, ...) \
    const ecs_entity_t entity = ecs_new_id(ecs_world); \
    ecs_set(ecs_world, entity, ComponentTranslation2, { x, y }); \
    ecs_set(ecs_world, entity, ComponentScreenText, { text, font_size, __VA_ARGS__ });

#define CREATE_ENTITY_WORLD_TIME(ecs_world, entity, x, y, text, font_size, ...) \
    CREATE_ENTITY_TEXT(ecs_world, entity, x, y, text, font_size, __VA_ARGS__) \
    ecs_add(ecs_world, entity, TagSetWorldTime);

#define CREATE_ENTITY_FPS(ecs_world, entity, x, y) \
    const ecs_entity_t entity = ecs_new_id(ecs_world); \
    ecs_set(ecs_world, entity, ComponentTranslation2, { x, y }); \
    ecs_add(ecs_world, entity, TagDrawFps);

void RegisterSampleApplication()
{
    ecs_world_t* ecs_world = GetApplicationEcsWorld();

    // Register Components
    REGISTER_COMPONENTS(ecs_world);

    // Register Simulation Systems
    RegisterSystemSetScreenTextWorldTime(ecs_world);

    // Register Presentation Systems
    RegisterSystemBeginDrawing(ecs_world);
    RegisterSystemClearBackground(ecs_world);
    RegisterSystemDrawText(ecs_world);
    RegisterSystemDrawFps(ecs_world);
    RegisterSystemEndDrawing(ecs_world);

    // Create Entities
    CREATE_ENTITY_CLEAR_BACKGROUND(ecs_world, entity_screen_clear_background, DARKGRAY);
    CREATE_ENTITY_TEXT(ecs_world, entity_congrats_text, GetScreenWidth() * 0.5f - 750, GetScreenHeight() * 0.5f, "Congrats! You created your first window! Powered by raylib", 50, LIGHTGRAY);
    CREATE_ENTITY_TEXT(ecs_world, entity_ticking_text, GetScreenWidth() * 0.5f - 200, GetScreenHeight() * 0.5f + 80, "flecs is ticking...", 20, LIGHTGRAY);
    CREATE_ENTITY_WORLD_TIME(ecs_world, entity_world_time, GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f + 80, "", 20, RED);
    CREATE_ENTITY_FPS(ecs_world, entity_fps, 10, 10);
}
