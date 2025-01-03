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

  private:
    static constexpr DWord MAX_SIZE = 1024 * 64;
    
    Byte data[MAX_SIZE];
  };
}

#endif