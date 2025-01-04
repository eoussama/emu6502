#include "cpu.hpp"

namespace Core
{
  CPU::CPU()
  {
    init();
  }

  void CPU::init()
  {
    _a = 0;
    _x = 0;
    _y = 0;

    _sp = 0xFF;
    _pc = 0xFFFC;

    _flags = PS();
  }

  void CPU::run(Mem& mem)
  {
    // TODO: Implement CPU
  }
}