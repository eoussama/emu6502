#include <iostream>

#include "core/emu6502.hpp"

int main()
{
  using namespace Core;

  CPU cpu;
  Mem mem;

  Byte program[1024 * 64] = {0};
  program[0xFFFC] = 0xA5;
  program[0xFFFD] = 0x42;
  program[0x0042] = 0x84;

  try
  {
    mem.load(program, sizeof(program));
    cpu.run(mem, 3);
  }
  catch (std::exception &e)
  {
    std::cerr << "[Error] " << e.what() << std::endl;
  }

  return 0;
}