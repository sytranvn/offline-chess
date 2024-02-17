set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB_RECURSE SOURCES "engine/*.cpp")
file(GLOB_RECURSE HEADERS "engine/*.h")
add_library(engine)
target_sources(
  engine
  PRIVATE ${SOURCES}
  PUBLIC ${HEADERS})
