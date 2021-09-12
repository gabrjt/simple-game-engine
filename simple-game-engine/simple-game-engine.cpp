#include <raylib.h>
#include <flecs.h>
#include <iostream>
#include <string>

// Sample ECS Components
struct Position {
    float x, y;

    std::string toString() {
        return "Position(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

struct Velocity {
    float x, y;
};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Create ECS World
    flecs::world ecs;

    // Create example position system
    ecs.system<Position, const Velocity>()
        .each([](flecs::entity e, Position& p, const Velocity& v) {
        const auto deltaTime = e.delta_time();
        p.x += v.x * deltaTime;
        p.y += v.y * deltaTime;
            });

    // Create entity with position and velocity components
    auto e = ecs.entity()
        .set([](Position& p, Velocity& v) {
        p = { 10, 20 };
        v = { 1, 2 };
            });
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Update ECS World with delta time
        ecs.progress(GetFrameTime());

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw text
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        // Draw entity position from query
        ecs.each([](flecs::entity e, Position& p) {
            DrawText(std::string("Entity at " + p.toString()).c_str(), 190, 230, 20, LIGHTGRAY);
            });

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}