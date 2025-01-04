#include "cpu.hpp"

namespace Core
{
  CPU::CPU()
  {
    init();
  }

  void CPU::init()
  {
    mA = 0;
    mX = 0;
    mY = 0;

    mSP = 0xFF;
    mPC = 0xFFFC;

    mFlags = PS();
  }

  void CPU::run(Mem &mem, Word cycles)
  {
    while (cycles > 0)
    {
      cycles--;
    }
  }
}