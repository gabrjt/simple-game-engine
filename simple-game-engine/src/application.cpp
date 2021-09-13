#include "application.h"
#include "raylib.h"

namespace sge
{
    application::application(const int screen_width, const int screen_height, const char* title, const int target_fps)
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
