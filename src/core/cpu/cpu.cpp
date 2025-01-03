#include "cpu.hpp"

namespace Core
{
  CPU::CPU()
  {
    init();
  }

  void CPU::init()
  {
    A = 0;
    X = 0;
    Y = 0;

    C = 0;
    Z = 0;
    I = 0;
    D = 0;
    B = 0;
    V = 0;
    N = 0;

    PC = 0;
    SP = 0xFF;
  }
}