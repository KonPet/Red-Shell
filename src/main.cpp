#include "Red_Shell.h"

int main(int argc, char* argv[])
{
    // std::cout << "\n\n___________________________\n\n\n\n";
    std::string name_in = get_name();
    std::vector <std::vector<int> > tile_grid = load_lvl(name_in);
    std::string lvl_name = "Editing ";
    // std::cout << name_in.c_str() << std::endl;
    if (name_in.length() > 0) {
        int it = name_in.length();
        int len = 0;
        while (name_in[it] != '\\' && it >= 0) {
            it--;
            len++;
            // std::cout << name_in[it];
        }
        for (int i = 0; i < len - 1; i++) {
            lvl_name += name_in[it + i + 1];
        }
        std::cout << lvl_name.c_str() << std::endl;
    }

    int screenWidth = 1248;
    int screenHeight = 800;

    Rectangle win1 = {16, 16, 1024, 768};
    Rectangle win2 = {1072, 16, 160, 128};
    Rectangle win3 = {1072, 176, 64, 32};
    Rectangle win4 = {1170, 176, 64, 32};
    Rectangle win5 = {1072, 240, 160, 544};


    Vector2 tile_list[19] = {{1072, 16}, {1104, 16}, {1136, 16}, {1168, 16}, {1200, 16}, {1072, 48}, {1104, 48}, {1136, 48}, {1168, 48}, {1200, 48}, {1072, 80}, {1104, 80}, {1136, 80}, {1168, 80}, {1200, 80}, {1072, 112}, {1104, 112}, {1136, 112}, {1168, 112}};
    int sel_tile = 0;
    int sel_tile2 = 1;
    int width = tile_grid[0].size();
    int height = tile_grid.size();
    int t_id;
    int left_draw_mode = 0;
    int right_draw_mode = 0;

    int offX = 0;
    int offY = 0;
    int speed = 1;
    bool x_off_add;
    bool y_off_add;

    Vector2 DragOrigin;

    bool left_erase;
    bool right_erase;
    Vector2 t_pos_temp;

    SetExitKey(KEY_ESCAPE);
    Image icon = LoadImage("Assets/RedShell.png");
    SetConfigFlags(!FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, lvl_name.c_str());
    SetWindowIcon(icon);

    Texture2D tiles[19] = {
        LoadTexture("tiles/Grass_0.png"),
        LoadTexture("tiles/Grass_1.png"),
        LoadTexture("tiles/Grass_2.png"),
        LoadTexture("tiles/Grass_3.png"),
        LoadTexture("tiles/Grass_4.png"),
        LoadTexture("tiles/Grass_5.png"),
        LoadTexture("tiles/Grass_6.png"),
        LoadTexture("tiles/Grass_7.png"),
        LoadTexture("tiles/Grass_8.png"),
        LoadTexture("tiles/Grass_9.png"),
        LoadTexture("tiles/Grass_10.png"),
        LoadTexture("tiles/Grass_11.png"),
        LoadTexture("tiles/Grass_12.png"),
        LoadTexture("tiles/Pipe_1.png"),
        LoadTexture("tiles/Pipe_2.png"),
        LoadTexture("tiles/Pipe_3.png"),
        LoadTexture("tiles/Pipe_4.png"),
        LoadTexture("tiles/Stone.png"),
        LoadTexture("tiles/barrier.png")
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec({(float) GetMouseX(), (float) GetMouseY()}, win2) && left_draw_mode == 2) {
                int buff_tile = Vec2InArray({(float) GetMouseX() - (GetMouseX() + 16) % 32, (float) GetMouseY() - (GetMouseY() + 16) % 32}, tile_list);
                if (buff_tile != -1 && buff_tile != sel_tile2) {
                    sel_tile = buff_tile;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), {win1.x, win1.y, win1.width, win1.height-1}) && left_draw_mode == 1) {
                if (left_erase) {
                    tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] = -1;
                } else {
                    tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] = sel_tile;
                }
            }
        }
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            if (CheckCollisionPointRec({(float) GetMouseX(), (float) GetMouseY()}, win2) && right_draw_mode == 2) {
                int buff_tile = Vec2InArray({(float) (GetMouseX() - (GetMouseX() + 16) % 32),(float) (GetMouseY() - (GetMouseY() + 16) % 32)}, tile_list);
                if (buff_tile != -1 && buff_tile != sel_tile) {
                    sel_tile2 = buff_tile;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), win1) && right_draw_mode == 1) {
                if (right_erase) {
                    tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] = -1;
                } else {
                    tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] = sel_tile2;
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), win1)) {
                left_draw_mode = 1;
                if (tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] == sel_tile) {
                    left_erase = true;
                } else {
                    left_erase = false;
                }
            } else if (CheckCollisionPointRec(GetMousePosition(), win2)) {
                left_draw_mode = 2;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            left_draw_mode = 0;
        }

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), win1)) {
                right_draw_mode = 1;
                if (tile_grid[(GetMouseY() - 16 + offY) / 32][(GetMouseX() - 16 + offX) / 32] == sel_tile2) {
                    right_erase = true;
                } else {
                    right_erase = false;
                }
            } else if (CheckCollisionPointRec(GetMousePosition(), win2)) {
                right_draw_mode = 2;
            }
        }

        if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
            right_draw_mode = 0;
        }

        if (IsKeyPressed(KEY_P)) {
            int t_buff = sel_tile;
            sel_tile = sel_tile2;
            sel_tile2 = t_buff;
        }

        if (IsKeyDown(KEY_D)) {
            offX += speed;
            while (offX + 1024 > width * 32) {
                offX--;
            }
        }
        if (IsKeyDown(KEY_A)) {
            offX -= speed;
            while (offX < 0) {
                offX++;
            }
        }
        if (IsKeyDown(KEY_W)) {
            offY -= speed;
            while (offY < 0) {
                offY++;
            }
        }
        if (IsKeyDown(KEY_S)) {
            offY += speed;
            while (offY + 768 > height * 32) {
                offY--;
            }
        }

        if (IsKeyPressed(KEY_COMMA) && speed > 1) {
            speed--;
        }
        if (IsKeyPressed(KEY_PERIOD)) {
            speed++;
        }

        if (IsKeyPressed(KEY_TAB)) {
            for (int i = 0; i < 18; i++) {
                UnloadTexture(tiles[i]);
            }
            CloseWindow();
            Vector2 dims = get_size(width, height);
            width = dims.x;
            height = dims.y;

            if (height != tile_grid.size() || width != tile_grid[0].size()) {
                int og_width = tile_grid[0].size();
                int og_height = tile_grid.size();
                std::vector<std::vector<int> > buff = tile_grid;
                tile_grid.clear();
                if (height <= og_height) {
                    if (width <= og_width) {
                        for (int y = 0; y < height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < width; x++) {
                                tile_grid[y].push_back(buff[y][x]);
                            }
                        }
                    } else {
                        for (int y = 0; y < height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < og_width; x++) {
                                tile_grid[y].push_back(buff[y][x]);
                            }
                            for (int x = 0; x < width - og_width; x++) {
                                tile_grid[y].push_back(-1);
                            }
                        }
                    }
                } else {
                    if (width <= og_width) {
                        for (int y = 0; y < og_height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < width; x++) {
                                tile_grid[y].push_back(buff[y][x]);
                            }
                        }
                        for (int y = 0; y < height - og_height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < width; x++) {
                                tile_grid[y + og_height].push_back(-1);
                            }
                        }
                    } else {
                        for (int y = 0; y < og_height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < og_width; x++) {
                                tile_grid[y].push_back(buff[y][x]);
                            }
                            for (int x = 0; x < width - og_width; x++) {
                                tile_grid[y].push_back(-1);
                            }
                        }
                        for (int y = 0; y < height - og_height; y++) {
                            tile_grid.push_back({});
                            for (int x = 0; x < width; x++) {
                                tile_grid[y + og_height].push_back(-1);
                            }
                        }
                    }
                }
            }
            SetExitKey(KEY_ESCAPE);
            SetConfigFlags(!FLAG_WINDOW_UNDECORATED);
            InitWindow(screenWidth, screenHeight, "Red Shell");
            SetWindowIcon(icon);
            SetTargetFPS(60);
            Texture2D buff_tiles[19] = {
                LoadTexture("tiles/Grass_0.png"),
                LoadTexture("tiles/Grass_1.png"),
                LoadTexture("tiles/Grass_2.png"),
                LoadTexture("tiles/Grass_3.png"),
                LoadTexture("tiles/Grass_4.png"),
                LoadTexture("tiles/Grass_5.png"),
                LoadTexture("tiles/Grass_6.png"),
                LoadTexture("tiles/Grass_7.png"),
                LoadTexture("tiles/Grass_8.png"),
                LoadTexture("tiles/Grass_9.png"),
                LoadTexture("tiles/Grass_10.png"),
                LoadTexture("tiles/Grass_11.png"),
                LoadTexture("tiles/Grass_12.png"),
                LoadTexture("tiles/Pipe_1.png"),
                LoadTexture("tiles/Pipe_2.png"),
                LoadTexture("tiles/Pipe_3.png"),
                LoadTexture("tiles/Pipe_4.png"),
                LoadTexture("tiles/Stone.png"),
                LoadTexture("tiles/barrier.png")
            };
            for (int i = 0; i < 18; i++) {
                tiles[i] = buff_tiles[i];
            }
            while (offX + 1024 > width * 32) {
                offX--;
            }
            while (offY + 768 > height * 32) {
                offY--;
            }
        }

        if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
            DragOrigin = GetMousePosition();
        }
        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
            offX += DragOrigin.x - GetMouseX();
            offY += DragOrigin.y - GetMouseY();
            DragOrigin = GetMousePosition();
            while (offY + 768 > height * 32) {
                offY--;
            }
            while (offY < 0) {
                offY++;
            }
            while (offX < 0) {
                offX++;
            }
            while (offX + 1024 > width * 32) {
                offX--;
            }
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginScissorModeRect(win1);
                ClearBackground(RAYWHITE);
                if (offX % 32 == 0) {
                    x_off_add = false;
                } else {
                    x_off_add = true;
                }
                if (offY % 32 == 0) {
                    y_off_add = false;
                } else {
                    y_off_add = true;
                }
                for (int grid_y = 0; grid_y < 24 + y_off_add; grid_y++) {
                    for (int grid_x = 0; grid_x < 32 + x_off_add; grid_x++) {
                        t_id = tile_grid[grid_y + (offY / 32)][grid_x + (offX / 32)];
                        if (t_id > -1) {
                            t_pos_temp = {grid_x * 32 + 16 - offX % 32, grid_y * 32 + 16 - offY % 32};
                            DrawTextureEx(tiles[t_id], t_pos_temp, 0, 2.0f, WHITE);
                        }
                    }
                }
            EndScissorMode();

            BeginScissorModeRect(win2);
                ClearBackground(RAYWHITE);
                DrawTextureEx(tiles[0], tile_list[0], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[1], tile_list[1], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[2], tile_list[2], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[3], tile_list[3], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[4], tile_list[4], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[5], tile_list[5], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[6], tile_list[6], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[7], tile_list[7], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[8], tile_list[8], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[9], tile_list[9], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[10], tile_list[10], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[11], tile_list[11], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[12], tile_list[12], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[13], tile_list[13], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[14], tile_list[14], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[15], tile_list[15], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[16], tile_list[16], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[17], tile_list[17], 0, 2.0f, WHITE);
                DrawTextureEx(tiles[18], tile_list[18], 0, 2.0f, WHITE);
                DrawRectangle(tile_list[sel_tile].x, tile_list[sel_tile].y, 32, 32, {230, 41, 55, 96});
                DrawRectangle(tile_list[sel_tile2].x, tile_list[sel_tile2].y, 32, 32, {0, 121, 241, 96});
            EndScissorMode();

            BeginScissorModeRect(win3);
                ClearBackground(RAYWHITE);
                DrawTextureEx(tiles[sel_tile], {1072, 176}, 0, 2, WHITE);
                DrawTextureEx(tiles[sel_tile2], {1104, 176}, 0, 2, WHITE);
            EndScissorMode();

            BeginScissorModeRect(win4);
                ClearBackground(RAYWHITE);
                DrawText(FormatText("%i", (int) round(1.0f / GetFrameTime())), 1170 + (64 - MeasureText(FormatText("%i", (int) round(1.0f / GetFrameTime())), 20)) / 2, 182, 20, RED);
            EndScissorMode();

            BeginScissorModeRect(win5);
                ClearBackground(RAYWHITE);
                DrawText(FormatText("WIDTH: %i", width), 1072 + (160 - MeasureText(FormatText("WIDTH: %i", width), 20)) / 2, 250, 20, BLACK);
                DrawText(FormatText("HEIGHT: %i", height), 1072 + (160 - MeasureText(FormatText("HEIGHT: %i", height), 20)) / 2, 275, 20, BLACK);
                DrawText(FormatText("X: %i", offX), 1072 + (160 - MeasureText(FormatText("X: %i", offX), 20)) / 2, 310, 20, RED);
                DrawText(FormatText("Y: %i", offY), 1072 + (160 - MeasureText(FormatText("Y: %i", offY), 20)) / 2, 335, 20, RED);
                DrawText(FormatText("Speed: %i", speed), 1072 + (160 - MeasureText(FormatText("Speed: %i", speed), 20)) / 2, 370, 20, BLUE);
            EndScissorMode();
        EndDrawing();
    }
 
    CloseWindow();
    save_lvl(tile_grid, name_in);
    
    return 0;
}