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

  SDWord CPU::run(Mem &mem, SDWord cycles)
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
        mA = peekByte(mem, cycles, zpAddress);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_ZPX:
      {
        Byte zpxAddress = stepByte(mem, cycles);
        Byte address = mX + zpxAddress;

        mA = peekByte(mem, --cycles, address);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_ABS:
      {
        Word address = stepWord(mem, cycles);
        mA = peekByte(mem, cycles, address);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_ABSX:
      {
        Word address = stepWord(mem, cycles);
        Word absAddressX = address + mX;

        mA = peekByte(mem, cycles, absAddressX);

        if (absAddressX - address >= 0xFF)
        {
          cycles--;
        }

        setLDAStatus();

        break;
      }

      case OpCode::LDA_ABSY:
      {
        Word address = stepWord(mem, cycles);
        Word absAddressY = address + mY;

        mA = peekByte(mem, cycles, absAddressY);

        if (absAddressY - address >= 0xFF)
        {
          cycles--;
        }

        setLDAStatus();

        break;
      }

      case OpCode::LDA_INDX:
      {
        Byte value = stepByte(mem, cycles);
        Byte zpAddress = value + mX;
        Word address = peekWord(mem, --cycles, zpAddress);

        mA = peekByte(mem, cycles, address);
        setLDAStatus();

        break;
      }

      case OpCode::LDA_INDY:
      {
        Byte zpAddress = stepByte(mem, cycles);
        Word effectiveAddress = peekWord(mem, cycles, zpAddress);
        Word address = effectiveAddress + mY;

        mA = peekByte(mem, cycles, address);

        if (address - effectiveAddress >= 0xFF)
        {
          cycles--;
        }

        setLDAStatus();

        break;
      }

      case OpCode::LDX_IM:
      {
        mX = stepByte(mem, cycles);
        setLDXStatus();

        break;
      }

      case OpCode::JSR:
      {
        Word address = stepWord(mem, cycles);
        writeWord(mem, cycles, mSP, mPC);

        mSP += 2;
        mPC = address;

        cycles--;

        break;
      }

      default:
      {
        throw InvalidOpCodeError(mPC, ins);
        break;
      }
      }
    }

    return initialCycles - cycles;
  }

  Byte CPU::stepByte(Mem &mem, SDWord &cycles)
  {
    Byte data = mem[mPC++];
    cycles--;

    return data;
  }

  Word CPU::stepWord(Mem &mem, SDWord &cycles)
  {
    Word data = mem[mPC++];
    data |= mem[mPC++] << 8;
    cycles -= 2;

    return data;
  }

  Byte CPU::peekByte(Mem &mem, SDWord &cycles, Word address)
  {
    Byte data = mem[address];
    cycles--;

    return data;
  }

  Word CPU::peekWord(Mem &mem, SDWord &cycles, Word address)
  {
    Byte lowByte = peekByte(mem, cycles, address);
    Byte highByte = peekByte(mem, cycles, address + 1);
    Word data = (highByte << 8) | lowByte;

    return data;
  }

  void CPU::writeWord(Mem &mem, SDWord &cycles, Word address, Word data)
  {
    mem[address] = data & 0xFF;
    mem[address + 1] = (data >> 8) & 0xFF;

    cycles -= 2;
  }

  void CPU::setLDAStatus()
  {
    mFlags.Z = mA == 0;
    mFlags.N = (mA & 0b10000000) > 0;
  }

  void CPU::setLDXStatus()
  {
    mFlags.Z = mX == 0;
    mFlags.N = (mX & 0b10000000) > 0;
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