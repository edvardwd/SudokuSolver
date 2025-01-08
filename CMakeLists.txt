cmake_minimum_required(VERSION 3.10)
project(sudoku)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib package
find_package(raylib REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Grid.cpp
    src/Tile.cpp
    src/utilities.cpp
    src/Button.cpp
)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)