# Visual sudoku solver
## Simple C++ project to showcase the solving of a Sudoku-board using recursive backtracking.
The finished product can also be found [here](https://www.edvardwd.folk.ntnu.no/build_web/sudoku.html)
## How to build and run
1. Make sure to have [raylib](https://github.com/raysan5/raylib) and [Emscripten](https://github.com/emscripten-core/emsdk) installed.
2. Clone this project and switch to the web branch
3. Open a terminal in the project folder and run
```
./buildWeb.sh
```
4. Enter the build_web folder and run
```
python3 -m http.server
```
or open sudoku.html with the live server VS Code extension.