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
        // Main game loop
        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: update simulation systems
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

            // Update ECS World with delta time
            // TODO: update presentation systems
            ecs_world_.progress(GetFrameTime());

            EndDrawing();
            //----------------------------------------------------------------------------------
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow(); // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
    }

    flecs::world& application::get_ecs_world()
    {
        return ecs_world_;
    }
}
