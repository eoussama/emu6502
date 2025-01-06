#include <gtest/gtest.h>
#include "core/emu6502.hpp"

namespace Core
{
  class LdxTest : public testing::Test
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

    void checkFlags(CPU &cpu, CPU &cpuCopy)
    {
      EXPECT_EQ(mCpu.getFlags().C, cpuCopy.getFlags().C);
      EXPECT_EQ(mCpu.getFlags().V, cpuCopy.getFlags().V);
      EXPECT_EQ(mCpu.getFlags().D, cpuCopy.getFlags().D);
      EXPECT_EQ(mCpu.getFlags().I, cpuCopy.getFlags().I);
      EXPECT_EQ(mCpu.getFlags().B, cpuCopy.getFlags().B);
    }

    CPU mCpu;
    Mem mMem;
  };

  TEST_F(LdxTest, LDXImmediateCanLoadAValueIntoTheXRegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[] = {0xA2, 0x84};

    mMem.load(program, sizeof(program), 0xFFFC);
    SDWord cycles = mCpu.run(mMem, 2);

    EXPECT_EQ(mCpu.getX(), 0x84);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_TRUE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 2);
  }
}