#include <gtest/gtest.h>
#include "core/emu6502.hpp"

namespace Core
{
  class LdaTest : public testing::Test
  {
  protected:
    void SetUp() override
    {
      mCpu.init();
      mMem.init();
    }

    void TearDown() override
    {
      mCpu.init();
      mMem.init();
    }

    CPU mCpu;
    Mem mMem;
  };

  TEST_F(LdaTest, LDA_IM)
  {
    Byte program[1024 * 64] = {0};
    program[0xFFFC] = 0xA9;
    program[0xFFFD] = 0x42;

    mMem.load(program, sizeof(program));
    mCpu.run(mMem, 2);

    EXPECT_EQ(mCpu.getA(), 0x42);
  }

  TEST_F(LdaTest, LDA_ZP)
  {
    Byte program[1024 * 64] = {0};
    program[0xFFFC] = 0xA5;
    program[0xFFFD] = 0x42;
    program[0x0042] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.run(mMem, 3);

    EXPECT_EQ(mCpu.getA(), 0x37);
  }

  TEST_F(LdaTest, LDA_ZPX)
  {
    Byte program[1024 * 64] = {0};
    program[0xFFFC] = 0xB5;
    program[0xFFFD] = 0x42;
    program[0x0047] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(5);
    mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
  }
}