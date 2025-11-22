#include <doctest/doctest.h>
#include <rvcpp/cpu.h>
#include <rvcpp/memory.h>

#include <iostream>
#include <memory>

TEST_CASE("RV32I Instruction Set Linear Execution") {
  auto mem = std::make_unique<rvcpp::Memory>();
  auto cpu = std::make_unique<rvcpp::CPU>(*mem);

  // We will execute instructions sequentially.
  // PC starts at 0.

  // 1. LUI (Load Upper Immediate)
  // lui x1, 0x12345
  // Binary: imm[31:12] | rd | opcode
  mem->write<uint32_t>(0, 0b00010010001101000101'00001'0110111);
  cpu->simulate(1);

  CHECK(cpu->read_register(1) == 0x12345000);
  CHECK(cpu->read_pc() == 4);

  // 2. AUIPC (Add Upper Immediate to PC)
  // auipc x2, 0x12345
  // PC is 4, so result is 4 + 0x12345000 = 0x12345004
  mem->write<uint32_t>(4, 0b00010010001101000101'00010'0010111);
  cpu->simulate(1);

  CHECK(cpu->read_register(2) == 0x12345004);
  CHECK(cpu->read_pc() == 8);

  // 3. JAL (Jump and Link)
  // jal x3, 8 (offset 8)
  // PC=8 -> PC=8+8=16. x3=8+4=12.
  // imm[20|10:1|11|19:12] | rd | opcode
  mem->write<uint32_t>(8, 0b0000000100'0'00000000'00011'1101111);
  cpu->simulate(1);

  CHECK(cpu->read_register(3) == 12);
  CHECK(cpu->read_pc() == 16);

  // 4. JALR (Jump and Link Register)
  // 16: addi x4, x0, 32
  mem->write<uint32_t>(16, 0b000000100000'00000'000'00100'0010011);
  // 20: jalr x5, x4, 4
  // Target = x4 + 4 = 36. x5 = PC + 4 = 24.
  mem->write<uint32_t>(20, 0b000000000100'00100'000'00101'1100111);

  cpu->simulate(2);

  CHECK(cpu->read_register(4) == 32);
  CHECK(cpu->read_register(5) == 24);
  CHECK(cpu->read_pc() == 36);

  // 5. Branch Instructions
  // 36: addi x6, x0, 10
  mem->write<uint32_t>(36, 0b000000001010'00000'000'00110'0010011);
  // 40: addi x7, x0, 20
  mem->write<uint32_t>(40, 0b000000010100'00000'000'00111'0010011);

  cpu->simulate(2);
  CHECK(cpu->read_register(6) == 10);
  CHECK(cpu->read_register(7) == 20);
  CHECK(cpu->read_pc() == 44);

  // BEQ (Not Taken)
  // 44: beq x6, x7, 8 (offset 8 -> target 52)
  // Not taken (10 != 20), PC should be 44 + 4 = 48
  mem->write<uint32_t>(44, 0b0'000000'00111'00110'000'0100'0'1100011);
  cpu->simulate(1);
  CHECK(cpu->read_pc() == 48);

  // BEQ (Taken)
  // 48: addi x6, x0, 20 (Overwrite x6 to be 20)
  mem->write<uint32_t>(48, 0b000000010100'00000'000'00110'0010011);
  // 52: beq x6, x7, 8 (offset 8 -> target 52 + 8 = 60)
  // Taken (20 == 20)
  mem->write<uint32_t>(52, 0b0'000000'00111'00110'000'0100'0'1100011);

  cpu->simulate(2);
  CHECK(cpu->read_pc() == 60);

  // BNE (Taken)
  // 60: addi x6, x0, 10 (Reset x6 to 10)
  mem->write<uint32_t>(60, 0b000000001010'00000'000'00110'0010011);
  // 64: bne x6, x7, 8 (offset 8 -> target 64 + 8 = 72)
  // Taken (10 != 20)
  mem->write<uint32_t>(64, 0b0'000000'00111'00110'001'0100'0'1100011);

  cpu->simulate(2);
  CHECK(cpu->read_pc() == 72);

  // BLT (Taken)
  // 72: blt x6, x7, 8 (offset 8 -> target 80)
  // Taken (10 < 20)
  mem->write<uint32_t>(72, 0b0'000000'00111'00110'100'0100'0'1100011);
  cpu->simulate(1);
  CHECK(cpu->read_pc() == 80);

  // BGE (Not Taken)
  // 80: bge x6, x7, 8 (offset 8 -> target 88)
  // Not taken (10 !>= 20), PC -> 84
  mem->write<uint32_t>(80, 0b0'000000'00111'00110'101'0100'0'1100011);
  cpu->simulate(1);
  CHECK(cpu->read_pc() == 84);

  // 6. Load/Store Instructions
  // 84: addi x8, x0, 0xAB
  mem->write<uint32_t>(84, 0b000010101011'00000'000'01000'0010011);
  // 88: sw x8, 100(x0)
  mem->write<uint32_t>(88, 0b0000011'01000'00000'010'00100'0100011);
  // 92: lw x9, 100(x0)
  mem->write<uint32_t>(92, 0b000001100100'00000'010'01001'0000011);

  cpu->simulate(3);
  CHECK(cpu->read_register(8) == 0xAB);
  CHECK(mem->read<uint32_t>(100) == 0xAB);
  CHECK(cpu->read_register(9) == 0xAB);
  CHECK(cpu->read_pc() == 96);

  // 7. Immediate Arithmetic
  // 96: addi x10, x0, -1
  mem->write<uint32_t>(96, 0b111111111111'00000'000'01010'0010011);
  // 100: slti x11, x10, 0
  mem->write<uint32_t>(100, 0b000000000000'01010'010'01011'0010011);
  // 104: andi x12, x10, 0xFF
  mem->write<uint32_t>(104, 0b000011111111'01010'111'01100'0010011);

  cpu->simulate(3);
  CHECK(cpu->read_register(10) == 0xFFFFFFFF);
  CHECK(cpu->read_register(11) == 1);
  CHECK(cpu->read_register(12) == 0xFF);
  CHECK(cpu->read_pc() == 108);

  // 8. Register Arithmetic
  // 108: addi x13, x0, 10
  mem->write<uint32_t>(108, 0b000000001010'00000'000'01101'0010011);
  // 112: addi x14, x0, 20
  mem->write<uint32_t>(112, 0b000000010100'00000'000'01110'0010011);
  // 116: add x15, x13, x14
  mem->write<uint32_t>(116, 0b0000000'01110'01101'000'01111'0110011);
  // 120: sub x16, x14, x13
  mem->write<uint32_t>(120, 0b0100000'01101'01110'000'10000'0110011);
  // 124: sll x17, x13, x14
  mem->write<uint32_t>(124, 0b0000000'01110'01101'001'10001'0110011);

  cpu->simulate(5);
  CHECK(cpu->read_register(13) == 10);
  CHECK(cpu->read_register(14) == 20);
  CHECK(cpu->read_register(15) == 30);
  CHECK(cpu->read_register(16) == 10);
  CHECK(cpu->read_register(17) == 0xA00000);
  CHECK(cpu->read_pc() == 128);
}
