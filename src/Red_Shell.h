#include "raylib.h"
#include <vector>
#include <fstream>
#include <iterator>
#include <time.h>
#include <math.h>

#define border 8

class Tile {
public:
    int id;
    int x;
    int y;
    int width;
    int height;
};

int get_byte_val(std::vector<int> byte_arr, int index);
int Vec2InArray(Vector2 vec2, Vector2 array[18]);

void save_lvl(std::vector<std::vector<int> > bytes);
void BeginScissorModeRect(Rectangle rect);

std::vector<int> bytes_from_int(int num);
std::vector<std::vector<int> > load_lvl (void);

Tile checkTile(std::vector <std::vector<int> >& level_data, int id, int checkX, int checkY);

Vector2 get_size(int width, int height);
