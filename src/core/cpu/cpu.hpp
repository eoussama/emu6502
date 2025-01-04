#ifndef CPU_HPP
#define CPU_HPP

#include "ps.hpp"
#include "mem.hpp"
#include "types.hpp"

namespace Core
{
  class CPU
  {
  public:
    CPU();

    void init();
    void run(Mem &mem, Word cycles);

  private:
    Byte step(Mem &mem, Word &cycles);

    // Program Counter
    Word mPC;

    // Stack Pointer
    Byte mSP;

    // Accumulator
    Byte mA;

    // X and Y registers
    Byte mX;
    Byte mY;

    // Processor Status
    PS mFlags;
  };
}

#endif