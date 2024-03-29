cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(chess)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if(NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    URL_HASH SHA256=98f049b9ea2a9c40a14e4e543eeea1a7ec3090ebdcd329c4ca2cf98bc9793482
  )
  FetchContent_GetProperties(raylib)
  if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES
        OFF
        CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Dependencies
set(NNG_VERSION 1.7.2)
find_package(nng ${NNG_VERSION} QUIET) # QUIET or REQUIRED
if(NOT nng_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    nng
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/nanomsg/nng/archive/refs/tags/v${NNG_VERSION}.tar.gz
    URL_HASH SHA256=40e6af7bdd5d02ee98ba8fe5fd5c149ce3e5a555f202cdc837e3ead2d7cc7534
  )
  FetchContent_GetProperties(nng)
  if(NOT nng_POPULATED) # Have we downloaded raylib yet?
    set(NNG_TESTS NO)
    FetchContent_Populate(nng)
    add_subdirectory(${nng_SOURCE_DIR} ${nng_BINARY_DIR})
  endif()
endif()

add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} raylib nng chess_lib)

file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

# Web Configurations
if(${PLATFORM} STREQUAL "Web")
  # Tell Emscripten to build an example.html file.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
