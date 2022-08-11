cmake_minimum_required(VERSION 3.5)
project(ascii-video-player)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
add_executable(
        ascii-video-player
        src/main.cpp
        src/terminal_size.cpp
        src/terminal_size.h 
        src/play_video.cpp
        src/play_video.h
        src/utils.cpp 
        src/utils.h 
        src/colors.h
        )

INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(ascii-video-player ${OpenCV_LIBS})

