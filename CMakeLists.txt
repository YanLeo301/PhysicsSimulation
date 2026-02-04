cmake_minimum_required(VERSION 3.14)
project(PhysicsSimulation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(raylib QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(PhysicsSimulation 
    main.cpp
    vec2Math.cpp
)

target_link_libraries(PhysicsSimulation raylib)