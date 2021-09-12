#include <flecs.h>
#include <raylib.h>
#include <string>

// Sample ECS Components
struct position
{
    float x, y;

    std::string to_string() const
    {
        return "position(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

struct velocity
{
    float x, y;

    std::string to_string() const
    {
        return "velocity(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screen_width  = 800;
    constexpr int screen_height = 450;

    InitWindow(screen_width, screen_height, "simple game engine powered by raylib and flecs");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Create ECS World
    flecs::world ecs;

    // Create example position system
    ecs.system<position, const velocity>()
       .each(
           [](const flecs::entity entity, position& position, const velocity& velocity)
           {
               const auto delta_time = entity.delta_time();
               position.x += velocity.x * delta_time;
               position.y += velocity.y * delta_time;
           }
       );

    // Create entity with position and velocity components
    flecs::entity entity = ecs.entity()
                              .set(
                                  [](position& position, velocity& velocity)
                                  {
                                      position = {10, 20};
                                      velocity = {1, 2};
                                  }
                              )
                              .set_name("MyEntity");

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
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
        ecs.each(
            [](flecs::entity entity, const position& position)
            {
                DrawText(std::string(std::string(entity.name()) + " " + std::string(position.to_string())).c_str(), 190, 230, 20, LIGHTGRAY);
            }
        );

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
