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
    void run(Mem& mem);

  private:
    // Program Counter
    Word _pc;

    // Stack Pointer
    Byte _sp;

    // Accumulator
    Byte _a;

    // X and Y registers
    Byte _x;
    Byte _y;

    // Processor Status
    PS _flags;
  };
}

#endif