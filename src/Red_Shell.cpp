#include "Red_Shell.h"

std::vector <std::vector<int> > load_lvl (std::string &name) {
    std::string lvl_name = "";
    if (name.size() > 0) {
        lvl_name = name;
    } else {
        lvl_name = new_name();
    }

    int width = 0;
    int height = 0;

    if (name.length() > 0) {
        std::ifstream input((const char*) lvl_name.c_str(), std::ios::binary);

        std::vector<int> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));
        input.close();

        for (int i = 0; i < bytes.size(); i++) {
            if (bytes[i] < 0) {
                bytes[i] += 256;
            }
        }

        if ((bytes[0], bytes[1], bytes[2], bytes[3]) == (80, 76, 86, 76)) {
            width = get_byte_val(bytes, 4);
            height = get_byte_val(bytes, 6);
        }
    } else {
        Vector2 dim = get_size(64, 48);
        width = dim.x;
        height = dim.y;
    }

    std::vector<std::vector<int> > tile_grid(height, std::vector<int> (width, -1));

    if (name.length() > 0) {
        std::ifstream input((const char*) lvl_name.c_str(), std::ios::binary);

        std::vector<int> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        for (int i = 0; i < bytes.size(); i++) {
            if (bytes[i] < 0) {
                bytes[i] += 256;
            }
        }
        int bg_num = get_byte_val(bytes, 8);
        int index = 14;
        while (get_byte_val(bytes, index) != 65535) {
            for (int h = 0; h < get_byte_val(bytes, index + 8); h++) {
                for (int w = 0; w < get_byte_val(bytes, index + 6); w++) {
                    tile_grid[get_byte_val(bytes, index + 4) + h][get_byte_val(bytes, index + 2) + w] = get_byte_val(bytes, index)-1;
                }
            }
            index += 10;
        }
    }
    name = lvl_name;
    return tile_grid;
}

std::vector<int> bytes_from_int(int num) {
    std::vector<int> arr = {0, 0};
    while (num > 255) {
        arr[0] += 1;
        num -= 256;
    }
    arr[1] = num;
    return arr;
}


int get_byte_val(std::vector<int> byte_arr, int index) {
    return byte_arr[index] * 256 + byte_arr[index + 1];
}

int Vec2InArray(Vector2 vec2, Vector2 array[18]) {
    for (int i = 0; i < 19; i++) {
        if (vec2.x == array[i].x && vec2.y == array[i].y) {
            return i;
        }
    }
    return -1;
}


void save_lvl(std::vector <std::vector<int> > lvl_data, std::string& name) {
    int id;
    Tile sav_tile;

    std::vector<int> bytes{80, 76, 86, 76};

    bytes.insert(bytes.end(), {bytes_from_int(lvl_data[0].size())[0], bytes_from_int(lvl_data[0].size())[1]});
    // cout << lvl_data.size() << endl;
    // cout << bytes_from_int(lvl_data.size())[0] << ", " << bytes_from_int(lvl_data.size())[1] << endl;
    bytes.insert(bytes.end(), {bytes_from_int(lvl_data.size())[0], bytes_from_int(lvl_data.size())[1]});
    bytes.insert(bytes.end(), {0, 10, 84, 73, 76, 69});
    // cout << "\n" << endl;
    // for (int i = 0; i < bytes.size(); i++) \\\\{
    //     cout << bytes[i] << " ";
    // }

    for (int y = 0; y < lvl_data.size(); y++) {
        for (int x = 0; x < lvl_data[1].size(); x++) {
            id = lvl_data[y][x];
            if (id > -1) {
                sav_tile = checkTile(lvl_data, id, x, y);
                bytes.insert(bytes.end(), {bytes_from_int(sav_tile.id)[0], bytes_from_int(sav_tile.id)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(sav_tile.x)[0], bytes_from_int(sav_tile.x)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(sav_tile.y)[0], bytes_from_int(sav_tile.y)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(sav_tile.width)[0], bytes_from_int(sav_tile.width)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(sav_tile.height)[0], bytes_from_int(sav_tile.height)[1]});
            }
        }
    }

    bytes.insert(bytes.end(), {255, 255, 83, 80, 82, 84, 255, 255});
    
    std::ofstream output((const char*) name.c_str(), std::ios::binary);
    std::vector<signed char> buff_vec;
    

    for (int i = 0; i < bytes.size(); i++) {
        buff_vec.push_back((signed char) bytes[i]);
    }

    signed char buff_str[buff_vec.size()];

    for (int i = 0; i < buff_vec.size(); i++) {
        buff_str[i] = buff_vec[i];
    }

    output.write((const char*) buff_str, buff_vec.size());
    output.close();
}

void BeginScissorModeRect(Rectangle rect) {
    DrawRectangle(rect.x-border, rect.y-border, rect.width+border*2, rect.height+border*2, LIGHTGRAY);
    BeginScissorMode(rect.x, rect.y, rect.width, rect.height);
}


Tile checkTile(std::vector <std::vector<int> >& level_data, int id, int checkX, int checkY) {
    Tile resTile = {id+1, checkX, checkY, 0, 0};
    bool yLoop = true;
    for (int x = checkX; x < level_data[0].size(); x++) {
        if (level_data[checkY][x] == id) {
            resTile.width++;
            // level_data[checkY][x] = -1;
        } else {
            break;
        }
    }
    for (int y = checkY; y < level_data.size(); y++) {
        for (int x = checkX; x < resTile.width + checkX; x++) {
            if (level_data[y][x] != id) {
                yLoop = false;
                break;
            }
        }
        if (!yLoop) {
            break;
        } else {
            resTile.height++;
            for (int x = checkX; x < resTile.width + checkX; x++) {
                level_data[y][x] = -1;
            }
        }
    }
    return resTile;
}


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

std::string get_name() {
    SetConfigFlags(!FLAG_WINDOW_UNDECORATED);
    Image icon = LoadImage("Assets/RedShell.png");
    InitWindow(768, 512, "Level name");
    SetWindowIcon(icon);
    SetTargetFPS(60);
    Rectangle rect_name;
    Font font = GetFontDefault();
    std::string dropped_file;

    SetExitKey(KEY_ENTER);

    // char dropped_file[];
    int count = 0;

    while (!WindowShouldClose()) {
        if (IsFileDropped()) {
            break;
        }

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawRectangle(8, 8, 752, 496, RAYWHITE);
            DrawText("Drop a level here or press", 164, 223, 30, SKYBLUE);
            DrawText("ENTER to make a new one", 176, 289, 30, SKYBLUE);
        EndDrawing();
    }
    std::vector<char> out;
    if (IsFileDropped()) {
        dropped_file = GetDroppedFiles(&count)[0];
    }
    CloseWindow();
    return dropped_file;
}

std::string new_name() {
    SetConfigFlags(!FLAG_WINDOW_UNDECORATED);
    Image icon = LoadImage("Assets/RedShell.png");
    InitWindow(786, 128, "Enter new name");
    SetWindowIcon(icon);
    SetExitKey(KEY_ENTER);
    std::string name = "";
    int key;
    int maxChars = 15;
    int chars = 0;
    while (!WindowShouldClose()) {
        key = GetKeyPressed();
        if (((key > 47 && 59 > key) || (key > 64 && 91 > key) || (key > 96 && 122 > key) || key == 46 || key == 45 || key == 95) && chars < maxChars) {
            chars++;
            name += (char) key;
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            name.pop_back();
        }

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawRectangle(8, 8, 770, 112, RAYWHITE);
        DrawText(name.c_str(), 16, 16, 64, RED);
        EndDrawing();
    }
    CloseWindow();
    return name + ".lvl";
}
