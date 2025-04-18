cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project3)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/lzy46/Desktop/COP 3503C/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(project3 src/main.cpp src/WelcomeWindow.cpp
        src/gamewindow.cpp
        src/gamewindow.h
        src/Tile.h
        src/Tile.cpp
        src/Leaderboard.cpp
        src/Leaderboard.h)
target_link_libraries(project3 sfml-system sfml-window sfml-graphics sfml-audio)