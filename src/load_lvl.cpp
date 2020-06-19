#include "raylib.h"
#include <vector>
#include <fstream>
#include <iterator>
#include "get_size.h"
#include <iostream>

using namespace std;

int get_byte_val(vector<int> byte_arr, int index);
int check_val(int val);
void save_lvl(vector<vector<int> > bytes);
vector<int> bytes_from_int(int num);

vector <vector<int> > load_lvl () {
    int width = 0;
    int height = 0;
    if (FileExists("level.lvl")) {
        std::ifstream input("level.lvl", std::ios::binary);

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
            cout << width << endl;
            cout << height << endl;
        }

        // ======int to signed char======
        // signed char test = 61;
        // cout << "\n\n" << test << "\n\n" << endl;

    } else {
        Vector2 sizes = get_size(width, height);
        width = (int) sizes.x;
        height = (int) sizes.y;
    }

    vector<vector<int> > tile_grid(height, vector<int> (width, -1));

    if (FileExists("level.lvl")) {
        std::ifstream input("level.lvl", std::ios::binary);

        std::vector<int> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        for (int i = 0; i < bytes.size(); i++) {
            if (bytes[i] < 0) {
                bytes[i] += 256;
            }
            // cout << bytes[i] << endl;
        }
        int bg_num = get_byte_val(bytes, 8);
        int index = 14;
        while (get_byte_val(bytes, index) != 65535) {
            for (int h = 0; h < get_byte_val(bytes, index + 8); h++) {
                for (int w = 0; w < get_byte_val(bytes, index + 6); w++) {
                    tile_grid[get_byte_val(bytes, index + 4 + h)][get_byte_val(bytes, index + 2 + w)] = get_byte_val(bytes, index)-1;
                    // cout << get_byte_val(bytes, index) << ", " << get_byte_val(bytes, index + 2) << ", " << get_byte_val(bytes, index + 4) << ", " << get_byte_val(bytes, index + 6) << ", " << get_byte_val(bytes, index + 8) <<  endl;
                }
            }
            index += 10;
            // cout << get_byte_val(bytes, index) << ", " << get_byte_val(bytes, index+2) << ", " << get_byte_val(bytes, index+4) << ", " << get_byte_val(bytes, index+6) << ", " << get_byte_val(bytes, index+8) << "\n";
        }
    }
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < tile_grid[i].size(); j++) {
    //         cout << tile_grid[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    // cout << tile_grid << endl;
    return tile_grid;
}

int get_byte_val(vector<int> byte_arr, int index) {
    return byte_arr[index] * 256 + byte_arr[index + 1];
}

void save_lvl(vector <vector<int> > lvl_data) {
    int id;

    vector<int> bytes{80, 76, 86, 76};
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
                bytes.insert(bytes.end(), {bytes_from_int(id + 1)[0], bytes_from_int(id + 1)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(x)[0], bytes_from_int(x)[1]});
                bytes.insert(bytes.end(), {bytes_from_int(y)[0], bytes_from_int(y)[1]});
                bytes.insert(bytes.end(), {0, 1, 0, 1});
            }
        }
    }
    bytes.insert(bytes.end(), {255, 255, 83, 80, 82, 84, 255, 255});
    
    ofstream output("level.lvl", std::ios::binary);
    vector<signed char> buff_vec;
    for (int i = 0; i < bytes.size(); i++) {
        buff_vec.push_back((signed char) bytes[i]);
    }
    signed char buff_str[bytes.size()];
    for (int i = 0; i < buff_vec.size(); i++) {
        buff_str[i] = buff_vec[i];
    }
    output.write((const char*) buff_str, buff_vec.size());
    output.close();
}

vector<int> bytes_from_int(int num) {
    vector<int> arr = {0, 0};
    while (num > 255) {
        arr[0] += 1;
        num -= 256;
    }
    arr[1] = num;
    return arr;
}
