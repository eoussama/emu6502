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

  void CPU::run(Mem &mem, Word cycles)
  {
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
        break;
      }

      default:
      {
        throw InvalidOpCodeError(ins);
        break;
      }
      }
    }
  }

  Byte CPU::stepByte(Mem &mem, Word &cycles)
  {
    Byte data = mem[mPC++];
    cycles--;

    return data;
  }

  Byte CPU::peek(Mem &mem, Word &cycles, Word address)
  {
    Byte data = mem[address];
    cycles--;

    return data;
  }

  void CPU::setLDAStatus()
  {
    mFlags.Z = mA == 0;
    mFlags.N = mA & 0b10000000 > 0;
  }
}