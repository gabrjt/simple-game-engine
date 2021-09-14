#pragma once

#include <raylib.h>

#define COMPONENT_SCREEN_TEXT_BUFFER_SIZE 64

typedef struct
{
    char  text[COMPONENT_SCREEN_TEXT_BUFFER_SIZE];
    int   font_size;
    Color color;
} ComponentScreenText;
