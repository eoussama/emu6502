#include <iostream>

#include "core/core.hpp"

int main()
{
  using namespace Core;

  CPU cpu;
  Mem mem;

  Byte program[] = {0xA9, 0x04};

  try
  {
    mem.load(program, sizeof(program), 0xFFFC);
    cpu.run(mem, sizeof(program) / sizeof(Byte));
  }
  catch (std::exception &e)
  {
    std::cerr << "[Error] " << e.what() << std::endl;
  }

  return 0;
}