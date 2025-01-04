add_executable(sandbox main.cpp)

target_link_libraries(sandbox PRIVATE core)
target_include_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/src)