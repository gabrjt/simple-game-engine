#pragma once

#include <flecs.h>

namespace sge
{
    class application
    {
        flecs::world ecs_world_;

    public:
        application(int screen_width, int screen_height, const char* title, int target_fps);

        void run() const;

        flecs::world& get_ecs_world();
    };
}
