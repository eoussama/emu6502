cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME emu6502)

project(${PROJECT_NAME})
include(${CMAKE_SOURCE_DIR}/version.cmake)

add_subdirectory(src/core)
add_subdirectory(src/sandbox)

option(ENABLE_TESTS "Enable building tests" ON)
if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()