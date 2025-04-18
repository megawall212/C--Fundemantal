cmake_minimum_required(VERSION 3.5)
project(HelloSFML)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set SFML_DIR to your installation path
set(SFML_DIR "C:/Users/lzy46/Desktop/COP 3503C/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

# Add these includes
include_directories(
        ${SFML_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(HelloSFML
        main.cpp
        WelcomeWindow.cpp
        WelcomeWindow.h
)

target_link_libraries(HelloSFML
        sfml-graphics
        sfml-window
        sfml-system
)