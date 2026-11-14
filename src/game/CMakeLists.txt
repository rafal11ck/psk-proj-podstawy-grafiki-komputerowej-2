include(FetchContent)

# Header-only text rendering library.
FetchContent_Declare(
  gl_text
  GIT_REPOSITORY https://github.com/vallentin/glText.git
  GIT_TAG master)
FetchContent_MakeAvailable(gl_text)
add_library(gl_text INTERFACE)
target_include_directories(gl_text INTERFACE ${gl_text_SOURCE_DIR})

# EXCLUDE_FROM_ALL: build only what the game needs.
FetchContent_Declare(
  engine
  GIT_REPOSITORY https://github.com/rafal11ck/opengl-3d-engine.git
  GIT_TAG main
  EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(engine)

add_executable(
  main
  gameLevel.cpp
  main.cpp
  brick.cpp
  ball.cpp
  game.cpp
  collisions.cpp
  scoreBar.cpp
)

target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE engine gl_text)

install(TARGETS main)
