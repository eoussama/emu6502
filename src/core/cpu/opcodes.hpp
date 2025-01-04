#ifndef OPCODES_HPP
#define OPCODES_HPP

#include "../common/types.hpp"

namespace Core
{
  enum OpCode
  {
    LDA_IM = 0xA9,
    LDA_ZP = 0xA5,
    LDA_ZPX = 0xB5,
    LDA_ABS = 0xAD,
    JSR = 0x20,
  };
}

#endif