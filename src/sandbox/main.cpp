#include <iostream>

#include "cpu.hpp"

int main()
{
  using namespace Core;

  CPU cpu;
  Mem mem;

  Byte program[] = {0xA9, 0x03};

  mem.load(program, sizeof(program), 0xFFFC);
  cpu.run(mem, sizeof(program) / sizeof(Byte));

  return 0;
}