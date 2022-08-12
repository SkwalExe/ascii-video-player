//
// Created by skwal on 8/10/22.
//

#ifndef ASCII_VIDEO_PLAYER_UTILS_H
#define ASCII_VIDEO_PLAYER_UTILS_H

void sleep(int ms);
void clear();
bool file_exists(char *fileName);
struct Params
{
    char *file = nullptr;
    bool show_status = false;
    bool stretch = false;
    bool colors = false;
    bool blocks = false;
    bool inverse = false;
    bool color_background = false;
    int black_level = 2;
};

int array_length(char const *array);
#endif // ASCII_VIDEO_PLAYER_UTILS_H
