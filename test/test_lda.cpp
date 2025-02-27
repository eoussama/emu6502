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

  TEST_F(LdaTest, LDAImmediateCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[] = {0xA9, 0x84};

    mMem.load(program, sizeof(program), 0xFFFC);
    SDWord cycles = mCpu.run(mMem, 2);

    EXPECT_EQ(mCpu.getA(), 0x84);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_TRUE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 2);
  }

  TEST_F(LdaTest, LDAImmediateCanLoadAZeroValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[] = {0xA9, 0x00};

    mMem.load(program, sizeof(program), 0xFFFC);
    SDWord cycles = mCpu.run(mMem, 2);

    EXPECT_EQ(mCpu.getA(), 0x00);
    EXPECT_TRUE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 2);
  }

  TEST_F(LdaTest, LDAZeroPageCanLoadAValueIntoTheARegister)
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
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 3);
  }

  TEST_F(LdaTest, LDAZeroPageXCanLoadAValueIntoTheARegister)
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
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 4);
  }

  TEST_F(LdaTest, LDAZeroPageXCanLoadValueIntoTheARegisterWhenItWraps)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB5;
    program[0xFFFD] = 0x80;
    program[0x007F] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(0xFF);
    SDWord cycles = mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 4);
  }

  TEST_F(LdaTest, LDAAbsoluteCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xAD;
    program[0xFFFD] = 0x80;
    program[0xFFFE] = 0x44;
    program[0x4480] = 0x37;

    mMem.load(program, sizeof(program));
    SDWord cycles = mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 4);
  }

  TEST_F(LdaTest, LDAAbsoluteXCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xBD;
    program[0xFFFD] = 0x80;
    program[0xFFFE] = 0x44;
    program[0x4481] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(0x01);
    SDWord cycles = mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 4);
  }

  TEST_F(LdaTest, LDAAbsoluteXCanLoadAValueIntoTheARegisterWhenItCrossesAPageBoundary)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xBD;
    program[0xFFFD] = 0x02;
    program[0xFFFE] = 0x44;
    program[0x4501] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(0xFF);
    SDWord cycles = mCpu.run(mMem, 5);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 5);
  }

  TEST_F(LdaTest, LDAAbsoluteYCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB9;
    program[0xFFFD] = 0x80;
    program[0xFFFE] = 0x44;
    program[0x4481] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setY(0x01);
    SDWord cycles = mCpu.run(mMem, 4);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 4);
  }

  TEST_F(LdaTest, LDAAbsoluteYCanLoadAValueIntoTheARegisterWhenItCrossesAPageBoundary)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB9;
    program[0xFFFD] = 0x02;
    program[0xFFFE] = 0x44;
    program[0x4501] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setY(0xFF);
    SDWord cycles = mCpu.run(mMem, 5);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 5);
  }

  TEST_F(LdaTest, LDAIndirectXCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xA1;
    program[0xFFFD] = 0x02;
    program[0x0006] = 0x00;
    program[0x0007] = 0x80;
    program[0x8000] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setX(0x04);
    SDWord cycles = mCpu.run(mMem, 6);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 6);
  }

  TEST_F(LdaTest, LDAIndirectYCanLoadAValueIntoTheARegister)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB1;
    program[0xFFFD] = 0x02;
    program[0x0002] = 0x00;
    program[0x0003] = 0x80;
    program[0x8004] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setY(0x04);
    SDWord cycles = mCpu.run(mMem, 5);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 5);
  }

  TEST_F(LdaTest, LDAIndirectYCanLoadAValueIntoTheARegisterWhenItCrossesAPageBoundary)
  {
    CPU cpuCopy = mCpu;
    Byte program[1024 * 64] = {0};

    program[0xFFFC] = 0xB1;
    program[0xFFFD] = 0x02;
    program[0x0002] = 0x02;
    program[0x0003] = 0x80;
    program[0x8101] = 0x37;

    mMem.load(program, sizeof(program));
    mCpu.setY(0xFF);
    SDWord cycles = mCpu.run(mMem, 6);

    EXPECT_EQ(mCpu.getA(), 0x37);
    EXPECT_FALSE(mCpu.getFlags().Z);
    EXPECT_FALSE(mCpu.getFlags().N);
    checkFlags(mCpu, cpuCopy);
    EXPECT_EQ(cycles, 6);
  }
}