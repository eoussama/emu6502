#ifndef MEM_HPP
#define MEM_HPP

#include "common.hpp"

namespace Core
{
  class Mem
  {
  public:
    Mem();

    void init();

    Byte operator[](DWord address) const;

  private:
    static constexpr DWord MAX_SIZE = 1024 * 64;

    Byte mData[MAX_SIZE];
  };
}

#endif