#ifndef CPU_HPP
#define CPU_HPP

#include "mem.hpp"
#include "common.hpp"

namespace Core
{
  class CPU
  {
  public:
    CPU();

    void init();

  private:
    Word PC;
    Byte SP;
    Byte A;
    Byte X;
    Byte Y;

    Byte C : 1;      // 0: Carry Flag
    Byte Z : 1;      // 1: Zero Flag
    Byte I : 1;      // 2: Interrupt disable
    Byte D : 1;      // 3: Decimal mode
    Byte B : 1;      // 4: Break
    Byte Unused : 1; // 5: Unused
    Byte V : 1;      // 6: Overflow
    Byte N : 1;      // 7: Negative
  };
}

#endif