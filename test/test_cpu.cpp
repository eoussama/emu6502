#include <gtest/gtest.h>
#include "core/emu6502.hpp"

namespace Core
{
  class CPUTest : public testing::Test
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

  TEST_F(CPUTest, CPUInitializesCorrectly)
  {
    EXPECT_EQ(mCpu.getA(), 0x00);
    EXPECT_EQ(mCpu.getX(), 0x00);
    EXPECT_EQ(mCpu.getY(), 0x00);

    EXPECT_EQ(mCpu.getSP(), 0xFF);
    EXPECT_EQ(mCpu.getPC(), 0xFFFC);

    EXPECT_FALSE(mCpu.getFlags().C);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().I);
    EXPECT_FALSE(mCpu.getFlags().D);
    EXPECT_FALSE(mCpu.getFlags().B);
    EXPECT_FALSE(mCpu.getFlags().V);
    EXPECT_FALSE(mCpu.getFlags().N);
  }

  TEST_F(CPUTest, CPUThrowsAnErrorWhenWeRunAnInvalidOpcode)
  {
    Byte program[] = {0xFF};
    mMem.load(program, sizeof(program), 0xFFFC);

    EXPECT_THROW(mCpu.run(mMem, 1), InvalidOpCodeError);
  }

  TEST_F(CPUTest, CPUDoesNothingWhenWeRunZeroCycles)
  {
    CPU cpuCopy = mCpu;
    SDWord cycles = mCpu.run(mMem, 0);

    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(mCpu.getA(), cpuCopy.getA());
    EXPECT_EQ(mCpu.getX(), cpuCopy.getX());
    EXPECT_EQ(mCpu.getY(), cpuCopy.getY());
    EXPECT_EQ(mCpu.getPC(), cpuCopy.getPC());
    EXPECT_EQ(mCpu.getSP(), cpuCopy.getSP());
    EXPECT_EQ(mCpu.getFlags().C, cpuCopy.getFlags().C);
    EXPECT_EQ(mCpu.getFlags().Z, cpuCopy.getFlags().Z);
    EXPECT_EQ(mCpu.getFlags().I, cpuCopy.getFlags().I);
    EXPECT_EQ(mCpu.getFlags().D, cpuCopy.getFlags().D);
    EXPECT_EQ(mCpu.getFlags().B, cpuCopy.getFlags().B);
    EXPECT_EQ(mCpu.getFlags().V, cpuCopy.getFlags().V);
    EXPECT_EQ(mCpu.getFlags().N, cpuCopy.getFlags().N);
  }

  TEST_F(CPUTest, CPUCanRunMoreCyclesThanRequestedIfRequired)
  {
    Byte program[] = {0xA9, 0x84};
    mMem.load(program, sizeof(program), 0xFFFC);
    SDWord cycles = mCpu.run(mMem, 1);

    EXPECT_EQ(cycles, 2);
  }
}