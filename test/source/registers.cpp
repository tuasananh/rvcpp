#include <doctest/doctest.h>
#include <rvcpp/registers.h>

TEST_CASE("Registers") {
  // Arbitrary initial values for testing
  uint32_t initial_pc = 0x1000;
  uint32_t initial_sp = 0x7FFFFFF0;
  uint32_t initial_gp = 0x10008000;

  rvcpp::Registers regs(initial_pc, initial_sp, initial_gp);

  SUBCASE("Initialization") {
    CHECK(regs.pc == initial_pc);
    CHECK(regs.read(2) == initial_sp);  // x2 is SP
    CHECK(regs.read(3) == initial_gp);  // x3 is GP
    CHECK(regs.read(0) == 0);           // x0 should be 0
  }

  SUBCASE("Zero Register (x0) Behavior") {
    // x0 should always be 0
    CHECK(regs.read(0) == 0);

    // Writing to x0 should be ignored
    regs.write(0, 0xDEADBEEF);
    CHECK(regs.read(0) == 0);
  }

  SUBCASE("General Purpose Registers (x1-x31)") {
    // Test a few registers
    regs.write(1, 0x12345678);
    CHECK(regs.read(1) == 0x12345678);

    regs.write(31, 0x87654321);
    CHECK(regs.read(31) == 0x87654321);

    // Ensure writing to one doesn't affect another
    regs.write(5, 0xAABBCCDD);
    CHECK(regs.read(1) == 0x12345678);
    CHECK(regs.read(5) == 0xAABBCCDD);
  }

  SUBCASE("Program Counter") {
    regs.pc = 0x2000;
    CHECK(regs.pc == 0x2000);
  }
}
