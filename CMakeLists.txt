cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
project(Boids)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/ CACHE PATH "Output directory of all executables.")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# GLUT
find_package(GLUT REQUIRED)

# Eigen
find_package(Eigen3 REQUIRED)

include_directories(inc third-party)
add_subdirectory(third-party)
add_subdirectory(src)
add_subdirectory(app)
