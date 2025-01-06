include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_all test_mem.cpp test_cpu.cpp test_lda.cpp test_ldx.cpp)
target_link_libraries(test_all PRIVATE core gtest gtest_main)

add_test(NAME Emu6502Test COMMAND test_all)