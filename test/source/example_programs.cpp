#include <doctest/doctest.h>
#include <rvcpp/cpu.h>
#include <rvcpp/memory.h>

#include <memory>

TEST_CASE("Fibonacci Sequence") {
  auto mem = std::make_unique<rvcpp::Memory>();
  auto cpu = std::make_unique<rvcpp::CPU>(*mem);

  // Calculate 7th Fibonacci number (should be 13)
  // 0, 1, 1, 2, 3, 5, 8, 13...

  // 0: li x1, 7      (N)
  // addi x1, x0, 7
  std::vector<uint32_t> program = {
      // addi x1, x0, 7 # x1 = N = 7
      0b00000000011100000000000010010011,  // 0
      // addi x2, x0, 0 # x2 = prev = 0
      0b00000000000000000000000100010011,  // 4
      // addi x3, x0, 1 # x3 = curr = 1
      0b00000000000100000000000110010011,  // 8
      // addi x4, x0, 1 # x4 = i = 1
      0b00000000000100000000001000010011,  // 12
      // bge x4, x1, 24 # if i >= N goto 36
      0b00000000000100100101110001100011,  // 16
      // add x5, x2, x3 # temp = prev + curr
      0b00000000001100010000001010110011,  // 20
      // addi x2, x3, 0 # prev = curr
      0b00000000000000011000000100010011,  // 24
      // addi x3, x5, 0 # curr = temp
      0b00000000000000101000000110010011,  // 28
      // addi x4, x4, 1 # i = i + 1
      0b00000000000100100000001000010011,  // 32
      // 36: j -20          (jump to 16),
      0b11111110110111111111000001101111,  // 36
      // addi x10, x3, 0
      0b00000000000000011000010100010011,  // 40
      // beq x0, x0, 0
      0b00000000000000000000000001100011  // 44
  };

  for (size_t i = 0; i < program.size(); ++i) {
    mem->write<uint32_t>(static_cast<uint32_t>(i * 4), program[i]);
  }

  // Run enough cycles
  cpu->simulate(100);

  CHECK(cpu->read_register(10) == 13);
}

TEST_CASE("Multiplication by Addition") {
  auto mem = std::make_unique<rvcpp::Memory>();
  auto cpu = std::make_unique<rvcpp::CPU>(*mem);

  // 5 * 4 = 20

  std::vector<uint32_t> program = {
      // addi x1, x0, 5
      0b00000000010100000000000010010011,  // 0
      // addi x2, x0, 4
      0b00000000010000000000000100010011,  // 4
      // addi x10, x0, 0
      0b00000000000000000000010100010011,  // 8
      // beq x2, x0, 16 # if x2 == 0 goto 28
      0b00000000000000010000100001100011,  // 12
      // add x10, x10, x1
      0b00000000000101010000010100110011,  // 16
      // addi x2, x2, -1 # x2 = x2 - 1
      0b11111111111100010000000100010011,  // 20
      // j -12 (jump to 12)
      0b11111111010111111111000001101111,  // 24
      // beq x0, x0, 0
      0b00000000000000000000000001100011,  // 28
  };

  for (size_t i = 0; i < program.size(); ++i) {
    mem->write<uint32_t>(static_cast<uint32_t>(i * 4), program[i]);
  }

  cpu->simulate(100);

  CHECK(cpu->read_register(10) == 20);
}