#include <doctest/doctest.h>
#include <rvcpp/memory.h>

TEST_CASE("Memory Operations") {
  static rvcpp::Memory mem;

  SUBCASE("Initial State") {
    CHECK(rvcpp::Memory::get_initial_program_counter() == 0);
    // Stack pointer should be at the top of memory (minus reserved)
    // 4GiB = 0x100000000, but 32-bit so 0xFFFFFFFF + 1?
    // MEMORY_SIZE = 4_GiB.
    // STACK_TOP_ADDRESS = MEMORY_SIZE - RESERVED_SIZE.
    // RESERVED_SIZE = 1_MiB.
    // So 4GiB - 1MiB.
    // 4 * 1024 * 1024 * 1024 - 1024 * 1024 = 0xFFF00000
    CHECK(rvcpp::Memory::get_initial_stack_pointer() == 0xFFF00000);
  }

  SUBCASE("Read/Write Data Segment (uint32_t)") {
    // Data segment starts at 1MB (0x100000)
    uint32_t addr = 0x100000;
    uint32_t val = 0xDEADBEEF;

    mem.write<uint32_t>(addr, val);
    CHECK(mem.read<uint32_t>(addr) == val);
  }

  SUBCASE("Read/Write Stack Segment (uint32_t)") {
    // Stack starts at STACK_BASE_ADDRESS and goes to STACK_TOP_ADDRESS
    // STACK_TOP = 0xFFF00000
    // STACK_SIZE = 1MB
    // STACK_BASE = 0xFFE00000
    uint32_t addr = 0xFFE00000;
    uint32_t val = 0xCAFEBABE;

    mem.write<uint32_t>(addr, val);
    CHECK(mem.read<uint32_t>(addr) == val);
  }

  // Haven't implemented heap yet
  // SUBCASE("Read/Write Heap Segment (uint8_t)") {
  //   // Heap starts after Data segment
  //   // DATA_BASE = 1MB, DATA_SIZE = 16MB
  //   // HEAP_BASE = 17MB = 0x1100000
  //   uint32_t addr = 0x1100000;
  //   uint8_t val = 0x42;

  //   mem.write<uint8_t>(addr, val);
  //   CHECK(mem.read<uint8_t>(addr) == val);
  // }

  SUBCASE("Read/Write Text Segment (Instruction)") {
    // Text starts at 0
    uint32_t addr = 0x0;
    uint32_t instr = 0x00000013;  // nop (addi x0, x0, 0)

    mem.write<uint32_t>(addr, instr);
    CHECK(mem.read<uint32_t>(addr) == instr);
  }

  SUBCASE("Misaligned Access") {
    // Writing 4 bytes at address 1 should fail
    CHECK_THROWS_AS(mem.write<uint32_t>(1, 0x12345678), std::runtime_error);
    CHECK_THROWS_AS(mem.read<uint32_t>(1), std::runtime_error);
  }

  SUBCASE("Out of Bounds Access") {
    // Accessing reserved memory at the very top
    // MEMORY_SIZE - 1
    uint32_t addr = 0xFFFFFFFF;
    CHECK_THROWS_AS(mem.read<uint8_t>(addr), std::runtime_error);
  }

  SUBCASE("Different Types") {
    uint32_t addr = 0x100000;

    mem.write<uint8_t>(addr, 0xAA);
    CHECK(mem.read<uint8_t>(addr) == 0xAA);

    mem.write<int16_t>(addr, -12345);
    CHECK(mem.read<int16_t>(addr) == -12345);
  }
}
