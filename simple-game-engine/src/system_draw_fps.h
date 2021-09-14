#pragma once

typedef struct ecs_world_t ecs_world_t;
typedef struct ecs_iter_t ecs_iter_t;

void RegisterSystemDrawFps(ecs_world_t* ecs_world);

static void SystemDrawFps(const ecs_iter_t* it);
