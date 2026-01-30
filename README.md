# PhysicsSimulation
A simple 2D physics simulation with collisions and gravity.

![Demo](assets/demo.gif)

## How to build

**Prerequisites:** C++14 compiler and [raylib](https://www.raylib.com/)

### Windows (Visual Studio)
Open 'PhysicsSimulation.sln' and press Ctrl + F5 to build and run

### Linux

```
sudo apt install libraylib-dev g++ -std=c++14 main.cpp -o PhysicsSimulation -lraylib -lGL -lpthread -ldl -lrt ./PhysicsSimulation
```

### macOS (Homebrew)

```
brew install raylib clang++ -std=c++14 main.cpp -o PhysicsSimulation -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo ./PhysicsSimulation
```

### CMake

```
git clone https://github.com/YanLeo301/PhysicsSimulation.git
cd PhysicsSimulation
mkdir build && cd build
cmake ..
cmake --build .
```

## Controls

Click left mouse button to spawn a ball with random radius and velocity.