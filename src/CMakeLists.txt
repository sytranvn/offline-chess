set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB_RECURSE HEADERS "engine/*.h")
file(GLOB_RECURSE SOURCES "engine/*.cpp")
add_library(chess_lib)
target_sources(
  chess_lib PRIVATE ${SOURCES} PUBLIC ${HEADERS})

