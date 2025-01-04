#include <gtest/gtest.h>
#include "core/mem/mem.hpp"

namespace Core
{

  // Test 1: Check memory initialization
  TEST(MemTest, Initialization)
  {
    Mem memory;

    for (DWord i = 0; i < Mem::MAX_SIZE; ++i)
    {
      EXPECT_EQ(memory[i], 0x00) << "Memory not initialized to zero at address: " << i;
    }
  }

  // Test 2: Check loading data into memory
  TEST(MemTest, LoadData)
  {
    Mem memory;

    DWord offset = 0x10;
    Byte data[] = {0x42, 0x37, 0xAA};
    DWord size = sizeof(data) / sizeof(data[0]);

    memory.load(data, size, offset);

    for (DWord i = 0; i < size; ++i)
    {
      EXPECT_EQ(memory[offset + i], data[i]) << "Memory mismatch at address: " << (offset + i);
    }
  }

  // Test 3: Overwrite data in memory
  TEST(MemTest, OverwriteData)
  {
    Mem memory;
    DWord address = 0x20;
    memory[0x20] = 0x55;

    EXPECT_EQ(memory[address], 0x55) << "Data not overwritten correctly at address: " << address;
  }
}
