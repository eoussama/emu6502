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
      mData[i] = 0x00;
    }
  }

  // TODO: assert data is in range
  // TODO: assert size is in range
  // TODO: assert offset is in range
  void Mem::load(Byte *data, DWord size, DWord offset)
  {
    for (DWord i = 0; i < size; i++)
    {
      mData[i + offset] = data[i];
    }
  }

  // TODO: assert address is in range
  Byte Mem::operator[](DWord address) const
  {
    return mData[address];
  }

  // TODO: assert address is in range
  Byte &Mem::operator[](DWord address)
  {
    return mData[address];
  }
}