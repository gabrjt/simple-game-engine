#pragma once

typedef struct ecs_world_t ecs_world_t;
typedef struct ecs_iter_t ecs_iter_t;

void RegisterSystemBeginDrawing(ecs_world_t* ecs_world);

static void SystemBeginDrawing(const ecs_iter_t* it);

void RegisterSystemEndDrawing(ecs_world_t* ecs_world);

static void SystemEndDrawing(const ecs_iter_t* it);
