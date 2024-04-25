include(FetchContent)

FetchContent_Declare(
  engine
  GIT_REPOSITORY https://github.com/rafal11ck/opengl-3d-engine.git
  GIT_TAG main)
FetchContent_MakeAvailable(engine)

# copy resurces
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

add_executable(main gameLevel.cpp main.cpp brick.cpp ball.cpp game.cpp)

target_include_directories(main PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(main engine)
