file(GLOB_RECURSE CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_definitions(core PRIVATE PROJECT_NAME="${PROJECT_NAME}")
target_compile_definitions(core PRIVATE GLOBAL_VERSION="${GLOBAL_VERSION}")