#include "raylib.h"

#define border 8

void BeginScissorModeRect(Rectangle rect) {
    DrawRectangle(rect.x-border, rect.y-border, rect.width+border*2, rect.height+border*2, LIGHTGRAY);
    BeginScissorMode(rect.x, rect.y, rect.width, rect.height);
}

int Vec2InArray(Vector2 vec2, Vector2 array[18]) {
    for (int i = 0; i < 19; i++) {
        if (vec2.x == array[i].x && vec2.y == array[i].y) {
            return i;
        }
    }
    return -1;
}
