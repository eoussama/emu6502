#ifndef CPU_HPP
#define CPU_HPP

#include "ps.hpp"
#include "../mem/mem.hpp"
#include "../common/types.hpp"

namespace Core
{
  class CPU
  {
  public:
    CPU();

    void init();
    void run(Mem &mem, Word cycles);

  private:
    Word stepWord(Mem &mem, Word &cycles);
    Byte stepByte(Mem &mem, Word &cycles);
    Byte peek(Mem &mem, Word &cycles, Word address);

    void writeWord(Mem &mem, Word &cycles, Word address, Word data);

    void setLDAStatus();

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