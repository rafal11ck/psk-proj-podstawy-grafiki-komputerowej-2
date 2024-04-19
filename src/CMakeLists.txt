cmake_minimum_required("VERSION" 3.29.2)
project("pgk2")

add_subdirectory("external/opengl-3d-engine")
include_directories("external/opengl-3d-engine/src/engine/include")
add_subdirectory("game")
