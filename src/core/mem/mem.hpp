#ifndef MEM_HPP
#define MEM_HPP

#include "../common/types.hpp"

namespace Core
{
  class Mem
  {
  public:
    Mem();

    void init();
    void load(Byte *data, DWord size, DWord offset = 0);

    Byte operator[](DWord address) const;

  private:
    static constexpr DWord MAX_SIZE = 1024 * 64;

    Byte mData[MAX_SIZE];
  };
}

#endif