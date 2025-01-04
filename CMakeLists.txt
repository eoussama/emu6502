cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME emu6502)

project(${PROJECT_NAME})
include(${CMAKE_SOURCE_DIR}/version.cmake)

include_directories(
  ${PROJECT_SOURCE_DIR}/src/core
  ${PROJECT_SOURCE_DIR}/src/core/mem
  ${PROJECT_SOURCE_DIR}/src/core/cpu
  ${PROJECT_SOURCE_DIR}/src/core/errors
)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="${PROJECT_NAME}")
target_compile_definitions(${PROJECT_NAME} PRIVATE GLOBAL_VERSION="${GLOBAL_VERSION}")
target_link_libraries(${PROJECT_NAME})