file(GLOB_RECURSE HEADERS "*.h")
list(TRANSFORM HEADERS REPLACE "[.]h" ".cpp" OUTPUT_VARIABLE SOURCES)
add_library(chess_lib)
target_sources(
  chess_lib
  PRIVATE ${SOURCES}
  PUBLIC ${HEADERS})

target_link_libraries(chess_lib raylib)
