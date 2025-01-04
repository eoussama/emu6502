#include <iostream>

#include "core/emu6502.hpp"

int main()
{
  using namespace Core;

  CPU cpu;
  Mem mem;

  Byte program[1024 * 64] = {0};
  program[0xFFFC] = 0x20;
  program[0xFFFD] = 0x42;
  program[0xFFFE] = 0x42;
  program[0x4242] = 0xA9;
  program[0x4243] = 0x84;

  try
  {
    mem.load(program, sizeof(program));
    cpu.run(mem, 8);
  }
  catch (std::exception &e)
  {
    std::cerr << "[Error] " << e.what() << std::endl;
  }

  return 0;
}