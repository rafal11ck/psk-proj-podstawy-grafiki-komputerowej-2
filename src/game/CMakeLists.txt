include(FetchContent)

FetchContent_Declare(
  engine
  GIT_REPOSITORY https://github.com/rafal11ck/opengl-3d-engine.git
  GIT_TAG main)
FetchContent_MakeAvailable(engine)


FetchContent_GetProperties(gl_text)
if(NOT gl_text_POPULATED)
    FetchContent_Populate(gl_text)
    add_library(gl_text INTERFACE)
    target_include_directories(gl_text INTERFACE ${gl_text_SOURCE_DIR})
endif()


# copy resurces
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)


set(CMAKE_CXX_STANDARD_REQUIRED 23)

add_executable(
  main
  gameLevel.cpp
  main.cpp
  brick.cpp
  ball.cpp
  game.cpp
  fileSystem.cpp
  collisions.cpp
  scoreBar.cpp
)

add_custom_command(
  TARGET main
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:main>)

target_include_directories(main PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(main engine gl_text)
