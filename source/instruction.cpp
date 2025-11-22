
#include <rvcpp/instruction.h>

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

}  // namespace rvcpp