#include <rvcpp/instruction.h>

#include <iostream>

namespace rvcpp {
  static constexpr uint32_t mask(uint32_t bits) { return (1u << bits) - 1; }

  uint32_t Instruction::op() const { return raw & mask(7); }
  uint32_t Instruction::rd() const { return (raw >> 7) & mask(5); }
  uint32_t Instruction::funct3() const { return (raw >> 12) & mask(3); }
  uint32_t Instruction::rs1() const { return (raw >> 15) & mask(5); }
  uint32_t Instruction::rs2() const { return (raw >> 20) & mask(5); }
  uint32_t Instruction::funct7() const { return (raw >> 25) & mask(7); }
  uint32_t Instruction::sign_extended_imm_i() const {
    return static_cast<uint32_t>(static_cast<int32_t>(raw) >> 20);
  }
  uint32_t Instruction::uimm() const { return (raw >> 20) & mask(5); }
  uint32_t Instruction::sign_extended_imm_s() const {
    uint32_t imm4_0 = (raw >> 7) & mask(5);
    uint32_t imm11_5 = (raw >> 25) & mask(7);
    uint32_t imm = (imm11_5 << 5) | imm4_0;
    return static_cast<uint32_t>(static_cast<int32_t>(imm << 20) >> 20);
  }
  uint32_t Instruction::branch_target_address() const {
    uint32_t imm11 = (raw >> 7) & mask(1);
    uint32_t imm4_1 = (raw >> 8) & mask(4);
    uint32_t imm10_5 = (raw >> 25) & mask(6);
    uint32_t imm12 = (raw >> 31) & mask(1);
    uint32_t imm
        = (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
    return static_cast<uint32_t>(static_cast<int32_t>(imm << 19) >> 19);
  }
  uint32_t Instruction::upimm() const { return raw & ~mask(12); }
  uint32_t Instruction::jump_target_address() const {
    uint32_t imm19_12 = (raw >> 12) & mask(8);
    uint32_t imm11 = (raw >> 20) & mask(1);
    uint32_t imm10_1 = (raw >> 21) & mask(10);
    uint32_t imm20 = (raw >> 31) & mask(1);
    uint32_t imm
        = (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
    return static_cast<uint32_t>(static_cast<int32_t>(imm << 11) >> 11);
  }
}  // namespace rvcpp