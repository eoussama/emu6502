#include <gtest/gtest.h>
#include "core/mem/mem.hpp"

namespace Core
{
  // Test 1: Check memory initialization
  TEST(MemTest, Initialization)
  {
    Mem memory;
    memory.init();

    // Verify all memory locations are initialized to 0
    for (DWord i = 0; i < Mem::MAX_SIZE; ++i)
    {
      EXPECT_EQ(memory[i], 0) << "Memory not initialized to zero at address: " << i;
    }
  }

  // Test 2: Check loading data into memory
  TEST(MemTest, LoadData)
  {
    Mem memory;
    memory.init();

    Byte data[] = {0x42, 0x37, 0xAA};
    DWord size = sizeof(data) / sizeof(data[0]);
    DWord offset = 0x10;

    memory.load(data, size, offset);

    // Verify the data is loaded correctly
    for (DWord i = 0; i < size; ++i)
    {
      EXPECT_EQ(memory[offset + i], data[i]) << "Memory mismatch at address: " << (offset + i);
    }
  }

  // Test 3: Check out-of-bounds access for reading
  TEST(MemTest, OutOfBoundsRead)
  {
    Mem memory;
    memory.init();

    EXPECT_THROW(memory[Mem::MAX_SIZE], std::out_of_range) << "Expected out_of_range exception for reading out of bounds.";
  }

  // Test 4: Check out-of-bounds access for writing
  TEST(MemTest, OutOfBoundsWrite)
  {
    Mem memory;
    memory.init();

    EXPECT_THROW(memory.load(nullptr, 1, Mem::MAX_SIZE), std::out_of_range) << "Expected out_of_range exception for writing out of bounds.";
  }

  // Test 5: Overwrite data in memory
  TEST(MemTest, OverwriteData)
  {
    Mem memory;
    memory.init();

    DWord address = 0x20;
    memory[address] = 0x55;

    // Verify the data is overwritten
    EXPECT_EQ(memory[address], 0x55) << "Data not overwritten correctly at address: " << address;
  }
}
