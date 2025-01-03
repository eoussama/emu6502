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
      data[i] = 0;
    }
  }
}