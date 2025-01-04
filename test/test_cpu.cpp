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

  TEST_F(CPUTest, Init)
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

  TEST_F(CPUTest, InvalidOpcode)
  {
    Byte program[] = {0xFF};

    mMem.load(program, sizeof(program), 0xFFFC);

    EXPECT_THROW(mCpu.run(mMem, 1), InvalidOpCodeError);
  }
}