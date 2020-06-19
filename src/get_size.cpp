#include "raylib.h"

Vector2 get_size(int width, int height) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(245, 96, "Size");
    SetTargetFPS(60);
    Rectangle rect_w;
    Rectangle rect_h;
    int key;
    bool box = 0;
    SetExitKey(KEY_ENTER);
    while (!WindowShouldClose()) {
        rect_w = {8, 8, MeasureText("WIDTH:  ", 30) + 13 + MeasureText(FormatText("%i", width), 30), 40};
        rect_h = {8, 48, MeasureText("WIDTH:  ", 30) + 13 + MeasureText(FormatText("%i", height), 30), 40};

        if (!box) {
            key = GetKeyPressed();
            if (47 < key && key < 59) {
                width = width * 10 + key - 48;
                if (width > 65535) {
                    width = 65535;
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                width /= 10;
            }
        }
        if (box) {
            key = GetKeyPressed();
            if (47 < key && key < 59) {
                height = height * 10 + key - 48;
                if (height > 65535) {
                    height = 65535;
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                height /= 10;
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect_w)) {
            box = 0;
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect_h)) {
            box = 1;
        }

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawRectangle(8, 8, 229, 80, RAYWHITE);
            if (box) {
                DrawRectangleRec(rect_h, {0, 121, 241, 64});
            } else {
                DrawRectangleRec(rect_w, {230, 41, 55, 64});
            }
            DrawText("WIDTH:  ", 13, 13, 30, BLACK);
            DrawText(FormatText("%i", width), MeasureText("WIDTH:  ", 30) + 13, 13, 30, BLACK);
            DrawRectangleLinesEx(rect_w, 3, RED);
            DrawText("HEIGHT:", 13, 53, 30, BLACK);
            DrawText(FormatText("%i", height), MeasureText("WIDTH:  ", 30) + 13, 53, 30, BLACK);
            DrawRectangleLinesEx(rect_h, 3, BLUE);
        EndDrawing();
    }
    CloseWindow();
    if (width < 64) {
        width = 64;
    }
    if (height < 48) {
        height = 48;
    }
    Vector2 sizes_arr;
    sizes_arr.x = width;
    sizes_arr.y = height;
    return sizes_arr;
}