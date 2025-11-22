#include <cstdint>

namespace rvcpp {

  class Instruction {
    uint32_t raw;

  public:
    Instruction(uint32_t raw_instruction) : raw(raw_instruction) {}

    uint32_t op() const;
    uint32_t rd() const;
    uint32_t funct3() const;
    uint32_t rs1() const;
    uint32_t rs2() const;
    uint32_t funct7() const;
    uint32_t sign_extended_imm_i() const;
    uint32_t uimm() const;
    uint32_t sign_extended_imm_s() const;
    uint32_t branch_target_address() const;
    uint32_t upimm() const;
    uint32_t jump_target_address() const;
  };
}  // namespace rvcpp