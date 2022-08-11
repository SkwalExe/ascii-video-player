//
// Created by skwal on 8/10/22.
//

#include "utils.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;


void sleep(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


// height -6 for the status
void clear() {
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#endif
}
