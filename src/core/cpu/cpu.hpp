#ifndef CPU_HPP
#define CPU_HPP

#include "ps.hpp"
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
    // Program Counter
    Word PC;

    // Stack Pointer
    Byte SP;

    // Accumulator
    Byte A;

    // X and Y registers
    Byte X;
    Byte Y;

    // Processor Status
    PS Flags;
  };
}

#endif