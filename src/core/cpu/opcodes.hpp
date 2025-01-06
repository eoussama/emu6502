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
    LDA_ABSX = 0xBD,
    LDA_ABSY = 0xB9,
    LDA_INDX = 0xA1,
    LDA_INDY = 0xB1,

    LDX_IM = 0xA2,

    JSR = 0x20,
  };
}

#endif