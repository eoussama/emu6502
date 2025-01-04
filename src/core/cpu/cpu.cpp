#include "cpu.hpp"

namespace Core
{
  CPU::CPU()
  {
    init();
  }

  void CPU::init()
  {
    A = 0;
    X = 0;
    Y = 0;

    SP = 0xFF;
    PC = 0xFFFC;

    Flags = PS();
  }
}