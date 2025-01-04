#include <iostream>

#include "cpu.hpp"

int main()
{
  using namespace Core;

  Mem mem;
  CPU cpu;

  cpu.run(mem, 2);

  return 0;
}