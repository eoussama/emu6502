#include "mem.hpp"

namespace Core
{
  Mem::Mem()
  {
    init();
  }

  void Mem::init()
  {
    for (DWord i = 0; i < MAX_SIZE; i++)
    {
      mData[i] = 0;
    }
  }

  // TODO: assert address is in range
  Byte Mem::operator[](DWord address) const
  {
    return mData[address];
  }
}