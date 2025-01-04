#include <gtest/gtest.h>
#include "core/emu6502.hpp"

namespace Core
{
  class MemTest : public testing::Test
  {
  protected:
    void SetUp() override
    {
      mMem.init();
    }

    void TearDown() override
    {
      mMem.init();
    }

    Mem mMem;
  };

  TEST_F(MemTest, Init)
  {
    for (DWord i = 0; i < Mem::MAX_SIZE; ++i)
    {
      EXPECT_EQ(mMem[i], 0x00) << "Memory not initialized to zero at address: " << i;
    }
  }

  TEST_F(MemTest, Load)
  {
    DWord offset = 0x10;
    Byte data[] = {0x42, 0x37, 0xAA};
    DWord size = sizeof(data) / sizeof(data[0]);

    mMem.load(data, size, offset);

    for (DWord i = 0; i < size; ++i)
    {
      EXPECT_EQ(mMem[offset + i], data[i]) << "Memory mismatch at address: " << (offset + i);
    }
  }

  TEST_F(MemTest, Override)
  {
    DWord address = 0x20;
    mMem[0x20] = 0x55;

    EXPECT_EQ(mMem[address], 0x55) << "Data not overwritten correctly at address: " << address;
  }
}