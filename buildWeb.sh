#!/bin/bash

# Configuration - users can modify these paths
RAYLIB_INCLUDE="${RAYLIB_INCLUDE:-$HOME/tools/raylib/build_web/raylib/include}"
RAYLIB_LIB="${RAYLIB_LIB:-$HOME/tools/raylib/build_web/raylib/libraylib.a}"
EMSDK_PATH="${EMSDK_PATH:-$HOME/tools/emsdk}"

# Clear JS and WASM files from the build directory
rm -rf build_web/*.js build_web/*.wasm
# Source Emscripten environment
source "$EMSDK_PATH/emsdk_env.sh"

# Build command - outputs ONLY .js and .wasm
emcc src/main.cpp src/Grid.cpp src/Tile.cpp src/utilities.cpp src/Button.cpp \
  -I"$RAYLIB_INCLUDE" \
  "$RAYLIB_LIB" \
  -o build_web/sudoku.js \
  -s USE_GLFW=3 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s ASYNCIFY=1 \
  -s 'ASYNCIFY_IMPORTS=["emscripten_sleep"]' \
  -s STACK_SIZE=2MB \
  -s INITIAL_MEMORY=64MB \
  -s MAXIMUM_MEMORY=256MB \
  -O2 \
  -flto