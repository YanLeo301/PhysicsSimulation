# PhysicsSimulation
A simple 2D physics simulation with collisions and gravity.

![Demo](assets/demo.gif)

## How to build

**Prerequisites:** C++14 compiler and [raylib](https://www.raylib.com/)

### Windows (Visual Studio)
Open 'PhysicsSimulation.sln' and press Ctrl + F5 to build and run

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
Click right mouse button on a ball to remove it.