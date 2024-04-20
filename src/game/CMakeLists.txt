include(FetchContent)

FetchContent_Declare(
  engine
  GIT_REPOSITORY https://github.com/rafal11ck/opengl-3d-engine.git
  GIT_TAG main)
FetchContent_MakeAvailable(engine)

add_executable(main main.cpp
        Game.cpp
        include/Game.hpp
        Ball.cpp
        include/Ball.hpp)
target_link_libraries(main engine)
