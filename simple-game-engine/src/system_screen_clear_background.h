#pragma once

typedef struct ecs_world_t ecs_world_t;
typedef struct ecs_iter_t ecs_iter_t;

void RegisterSystemClearBackground(ecs_world_t* ecs_world);

static void SystemClearBackground(const ecs_iter_t* it);
