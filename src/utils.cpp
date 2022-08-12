//
// Created by skwal on 8/10/22.
//

#include "utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;


void sleep(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void clear() {
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif
}

bool file_exists(char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

int array_length(char const *array)
{
    int i = 0;
    while (array[i] != '\0')
        i++;
    return i;
}