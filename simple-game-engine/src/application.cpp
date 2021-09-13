#include "application.h"
#include "raylib.h"

namespace sge
{
    application::application(int screen_width, int screen_height, const char* title, int target_fps)
    {
        InitWindow(screen_width, screen_height, title);
        SetTargetFPS(target_fps);
    }

    void application::run() const
    {
        while (!WindowShouldClose())
        {
            ecs_world_.progress(GetFrameTime());
        }

        CloseWindow();
    }

    flecs::world& application::get_ecs_world()
    {
        return ecs_world_;
    }
}
