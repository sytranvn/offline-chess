set(GOOGLETEST_VERSION 1.14.0)
find_package(googletest ${GOOGLETEST_VERSION} QUIET) # QUIET or REQUIRED
if(NOT googletest_FOUND) # If there's none, fetch and build googletest
  include(FetchContent)
  FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/google/googletest/archive/refs/tags/v${GOOGLETEST_VERSION}.tar.gz
  )
  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED) # Have we downloaded googletest yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(googletest)
    set(INSTALL_GTEST
        OFF
        CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()
endif()

include_directories(${chess_SOURCE_DIR})

if (APPLE)
  # If we are using the system clang, we need to disable coverage
  # https://stackoverflow.com/a/31543058/2945428
  set(GCC_GENERATE_TEST_COVERAGE_FILES NO)
  set(GCC_INSTRUMENT_PROGRAM_FLOW_ARCS NO)
else()
  set(CMAKE_CXX_FLAGS --coverage)
endif()

file(GLOB TEST_SOURCES "*.cpp")
add_executable(chess_test ${TEST_SOURCES})
target_link_libraries(chess_test GTest::gtest_main engine)

include(GoogleTest)
gtest_discover_tests(chess_test)
