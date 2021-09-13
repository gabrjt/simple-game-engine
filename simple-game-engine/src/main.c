#include <flecs.h>
#include <raylib.h>

#define SCREEN_TEXT_BUFFER_SIZE 64

typedef struct
{
    float x, y;
} Position;

typedef struct
{
    Color value;
} ScreenClearBackground;

typedef struct
{
    char  text[SCREEN_TEXT_BUFFER_SIZE];
    int   font_size;
    Color color;
} ScreenText;

void SetDisplayWorldTimeSystem(const ecs_iter_t* it)
{
    ScreenText* screen_text_components = ecs_term(it, ScreenText, 1);

    for (int i = 0; i < it->count; i++)
    {
        sprintf_s(screen_text_components[i].text, SCREEN_TEXT_BUFFER_SIZE, "%f", it->world_time);
    }
}

void BeginDrawingSystem(ecs_iter_t* it)
{
    BeginDrawing();
}

void ClearBackgroundSystem(const ecs_iter_t* it)
{
    const ScreenClearBackground* screen_clear_background_components = ecs_term(it, ScreenClearBackground, 1);

    for (int i = 0; i < it->count; i++)
    {
        ClearBackground(screen_clear_background_components[i].value);
    }
}

void DrawTextSystem(const ecs_iter_t* it)
{
    const ScreenText* screen_text_components = ecs_term(it, ScreenText, 1);
    const Position*   position_components    = ecs_term(it, Position, 2);

    for (int i = 0; i < it->count; i++)
    {
        const ScreenText* screen_text = &screen_text_components[i];
        const Position*   position    = &position_components[i];

        DrawText(screen_text->text, position->x, position->y, screen_text->font_size, screen_text->color);
    }
}

void EndDrawingSystem(ecs_iter_t* it)
{
    EndDrawing();
}

int main(int argc, char* argv[])
{
    // Init raylib window
    InitWindow(1920, 1080, "Cmple Game Engine");
    SetTargetFPS(60);

    // Create flecs ECS world
    ecs_world_t* ecs_world = ecs_init_w_args(argc, argv);

    // Register Components
    ECS_COMPONENT(ecs_world, Position);
    ECS_COMPONENT(ecs_world, ScreenClearBackground);
    ECS_COMPONENT(ecs_world, ScreenText);
    ECS_TAG(ecs_world, DisplayWorldTime);

    // Register Simulation Systems
    ECS_SYSTEM(ecs_world, SetDisplayWorldTimeSystem, EcsOnUpdate, ScreenText, DisplayWorldTime);

    // Register Presentation Systems
    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = {EcsPostUpdate}
            },
            .callback = BeginDrawingSystem
        }
    );

    ECS_SYSTEM(ecs_world, ClearBackgroundSystem, EcsPostUpdate, ScreenClearBackground);

    ECS_SYSTEM(ecs_world, DrawTextSystem, EcsPostUpdate, ScreenText, Position);

    ecs_system_init(
        ecs_world,
        &(ecs_system_desc_t) {
            .entity = {
                .add = {EcsPostUpdate}
            },
            .callback = EndDrawingSystem
        }
    );

    // Create Entities
    const ecs_entity_t entity_screen_clear_background = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_screen_clear_background, ScreenClearBackground, { DARKGRAY });

    const ecs_entity_t entity_congrats_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_congrats_text, Position, { GetScreenWidth() * 0.5f - 750, GetScreenHeight() * 0.5f });
    ecs_set(ecs_world, entity_congrats_text, ScreenText, { "Congrats! You created your first window! Powered by raylib", 50, LIGHTGRAY });

    const ecs_entity_t entity_ticking_text = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_ticking_text, Position, { GetScreenWidth() * 0.5f - 200, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_ticking_text, ScreenText, { "flecs is ticking...", 20, LIGHTGRAY });

    const ecs_entity_t entity_display_world_time = ecs_new_id(ecs_world);
    ecs_set(ecs_world, entity_display_world_time, Position, { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f + 80 });
    ecs_set(ecs_world, entity_display_world_time, ScreenText, { "", 20, RED });
    ecs_add(ecs_world, entity_display_world_time, DisplayWorldTime);

    // Game Loop
    while (!WindowShouldClose())
    {
        ecs_progress(ecs_world, GetFrameTime());
    }

    // Release resources
    CloseWindow();

    ecs_fini(ecs_world);

    // Exit
    return 0;
}
