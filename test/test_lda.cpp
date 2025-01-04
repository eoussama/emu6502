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
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xA9;
    program[0xFFFD] = 0x42;

    mMem.load(program, sizeof(program));
    SDWord cycles = mCpu.run(mMem, 2);

    EXPECT_EQ(mCpu.getA(), 0x42);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    EXPECT_EQ(mCpu.getFlags().C, cpuCopy.getFlags().C);
    EXPECT_EQ(mCpu.getFlags().V, cpuCopy.getFlags().V);
    EXPECT_EQ(mCpu.getFlags().D, cpuCopy.getFlags().D);
    EXPECT_EQ(mCpu.getFlags().I, cpuCopy.getFlags().I);
    EXPECT_EQ(mCpu.getFlags().B, cpuCopy.getFlags().B);
    EXPECT_EQ(cycles, 2);
  }

  TEST_F(LdaTest, LDA_ZP)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xA5;
    program[0xFFFD] = 0x42;
    program[0x0042] = 0x37;

    mMem.load(program, sizeof(program));
    SDWord cycles = mCpu.run(mMem, 3);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_TRUE(mCpu.getFlags().N);
    EXPECT_EQ(mCpu.getFlags().C, cpuCopy.getFlags().C);
    EXPECT_EQ(mCpu.getFlags().V, cpuCopy.getFlags().V);
    EXPECT_EQ(mCpu.getFlags().D, cpuCopy.getFlags().D);
    EXPECT_EQ(mCpu.getFlags().I, cpuCopy.getFlags().I);
    EXPECT_EQ(mCpu.getFlags().B, cpuCopy.getFlags().B);
    EXPECT_EQ(cycles, 3);
  }

  TEST_F(LdaTest, LDA_ZPX)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB5;
    program[0xFFFD] = 0x42;
    program[0x0047] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(5);
    SDWord cycles = mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_TRUE(mCpu.getFlags().N);
    EXPECT_EQ(mCpu.getFlags().C, cpuCopy.getFlags().C);
    EXPECT_EQ(mCpu.getFlags().V, cpuCopy.getFlags().V);
    EXPECT_EQ(mCpu.getFlags().D, cpuCopy.getFlags().D);
    EXPECT_EQ(mCpu.getFlags().I, cpuCopy.getFlags().I);
    EXPECT_EQ(mCpu.getFlags().B, cpuCopy.getFlags().B);
    EXPECT_EQ(cycles, 4);
  }
}