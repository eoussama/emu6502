#include "cpu.hpp"
#include "opcodes.hpp"
#include "../errors/invalid_opcode.hpp"

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

  SDWord CPU::run(Mem &mem, Word cycles)
  {
    const SDWord initialCycles = cycles;

    while (cycles > 0)
    {
      Byte ins = stepByte(mem, cycles);

      switch (ins)
      {
      case OpCode::LDA_IM:
      {
        mA = stepByte(mem, cycles);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_ZP:
      {
        Byte zpAddress = stepByte(mem, cycles);
        mA = peek(mem, cycles, zpAddress);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_ZPX:
      {
        Byte zpxAddress = stepByte(mem, cycles);
        Byte address = mX + zpxAddress;

        mA = peek(mem, --cycles, address);
        setLDAStatus();

        break;
      }

      case OpCode::JSR:
      {
        Word address = stepWord(mem, cycles);
        writeWord(mem, cycles, mSP, mPC);

        mPC = address;
        cycles--;

        break;
      }

      default:
      {
        throw InvalidOpCodeError(ins);
        break;
      }
      }
    }

    return initialCycles - cycles;
  }

  Byte CPU::stepByte(Mem &mem, Word &cycles)
  {
    Byte data = mem[mPC++];
    cycles--;

    return data;
  }

  Word CPU::stepWord(Mem &mem, Word &cycles)
  {
    Word data = mem[mPC++];
    data |= mem[mPC++] << 8;
    cycles -= 2;

    return data;
  }

  Byte CPU::peek(Mem &mem, Word &cycles, Word address)
  {
    Byte data = mem[address];
    cycles--;

    return data;
  }

  void CPU::writeWord(Mem &mem, Word &cycles, Word address, Word data)
  {
    mem[address] = data & 0xFF;
    mem[address + 1] = (data >> 8) & 0xFF;

    cycles -= 2;
  }

  void CPU::setLDAStatus()
  {
    mFlags.Z = mA == 0;
    mFlags.N = mA & 0b10000000 > 0;
  }

  PS CPU::getFlags() const
  {
    return mFlags;
  }

  Byte CPU::getA() const
  {
    return mA;
  }

  Byte CPU::getX() const
  {
    return mX;
  }

  Byte CPU::getY() const
  {
    return mY;
  }

  Word CPU::getPC() const
  {
    return mPC;
  }

  Byte CPU::getSP() const
  {
    return mSP;
  }

  void CPU::setA(Byte value)
  {
    mA = value;
  }

  void CPU::setX(Byte value)
  {
    mX = value;
  }

  void CPU::setY(Byte value)
  {
    mY = value;
  }

  void CPU::setPC(Word value)
  {
    mPC = value;
  }

  void CPU::setSP(Byte value)
  {
    mSP = value;
  }

  void CPU::setFlags(PS value)
  {
    mFlags = value;
  }
}