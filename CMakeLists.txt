cmake_minimum_required(VERSION 3.11)
project(PhysicsSimulation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib
find_package(raylib QUIET)

# If raylib is not found, download it automatically
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Create executable
add_executable(PhysicsSimulation main.cpp)

# Link raylib
target_link_libraries(PhysicsSimulation raylib)

# Copy executable to root directory for convenience
set_target_properties(PhysicsSimulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)