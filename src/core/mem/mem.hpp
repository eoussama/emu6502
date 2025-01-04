#ifndef MEM_HPP
#define MEM_HPP

#include "types.hpp"

namespace Core
{
  class Mem
  {
  public:
    Mem();

    void init();
    void load(Byte *data, DWord size, DWord offset);

    Byte operator[](DWord address) const;

  private:
    static constexpr DWord MAX_SIZE = 1024 * 64;

    Byte mData[MAX_SIZE];
  };
}

#endif