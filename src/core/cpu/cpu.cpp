#include "cpu.hpp"
#include <stdio.h>
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
      Byte ins = step(mem, cycles);
      printf("%02X\n", ins);
    }
  }

  Byte CPU::step(Mem &mem, Word &cycles)
  {
    Byte data = mem[mPC++];
    cycles--;

    return data;
  }
}