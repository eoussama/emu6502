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
    SDWord run(Mem &mem, SDWord cycles);

    Byte getA() const;
    Byte getX() const;
    Byte getY() const;
    Word getPC() const;
    Byte getSP() const;
    PS getFlags() const;

    void setA(Byte value);
    void setX(Byte value);
    void setY(Byte value);
    void setPC(Word value);
    void setSP(Byte value);
    void setFlags(PS value);

  private:
    Byte stepByte(Mem &mem, SDWord &cycles);
    Word stepWord(Mem &mem, SDWord &cycles);
    Byte peek(Mem &mem, SDWord &cycles, Word address);

    void writeWord(Mem &mem, SDWord &cycles, Word address, Word data);

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