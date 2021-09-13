#include <flecs.h>
#include <raylib.h>
#include <string>
#include "application.h"

struct screen_clear_background_component
{
    Color value;
};

struct position_component
{
    float x, y;
};

struct screen_text_component
{
    std::string text;
    int         font_size;
    Color       color;
};

struct display_world_time_tag {};

int main()
{
    sge::application application(1920, 1080, "My First App", 60);

    const flecs::world& ecs_world = application.get_ecs_world();

    ecs_world
        .entity("ClearBackground")
        .set(screen_clear_background_component{DARKGRAY});

    ecs_world
        .entity("CongratsText")
        .set(position_component{GetScreenWidth() * 0.5f - 500, GetScreenHeight() * 0.5f})
        .set(screen_text_component{"Congrats! You created your first window!", 50, LIGHTGRAY});

    ecs_world
        .entity("TickingText")
        .set(position_component{GetScreenWidth() * 0.5f - 200, GetScreenHeight() * 0.5f + 80})
        .set(screen_text_component{"flecs is ticking... ", 20, LIGHTGRAY});

    ecs_world
        .entity("WorldTimeText")
        .set(position_component{GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f + 80})
        .set(screen_text_component{std::string(), 20, RED})
        .add<display_world_time_tag>();

    // Simulation systems
    ecs_world
        .system<screen_text_component, display_world_time_tag>()
        .kind(flecs::OnUpdate)
        .iter(
            [](const flecs::iter it, screen_text_component* screen_text_component, const display_world_time_tag* _)
            {
                screen_text_component->text = std::to_string(it.world_time());
            }
        );

    // Presentation systems
    ecs_world
        .system()
        .kind(flecs::PostUpdate)
        .iter(
            [](const flecs::iter it)
            {
                BeginDrawing();
            }
        );

    ecs_world
        .system<screen_clear_background_component>()
        .kind(flecs::PostUpdate)
        .each(
            [](const screen_clear_background_component& screen_clear_background_component)
            {
                ClearBackground(screen_clear_background_component.value);
            }
        );

    ecs_world
        .system<screen_text_component, position_component>()
        .kind(flecs::PostUpdate)
        .each(
            [](const screen_text_component& screen_text_component, const position_component& position_component)
            {
                DrawText(screen_text_component.text.c_str(), position_component.x, position_component.y, screen_text_component.font_size, screen_text_component.color);
            }
        );

    ecs_world
        .system()
        .kind(flecs::PostUpdate)
        .iter(
            [](const flecs::iter it)
            {
                EndDrawing();
            }
        );

    application.run();

    return 0;
}
