#include <rvcpp/cpu.h>

namespace rvcpp {
  void CPU::opcode_0010011(const Instruction& instr) {
    switch (instr.funct3()) {
      case 0b000: {  // addi rd, rs1, imm
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        + instr.sign_extended_imm_i());
        break;
      }
      case 0b001: {  // slli rd, rs1, uimm
        switch (instr.funct7()) {
          case 0b0000000: {
            registers.write(instr.rd(), registers.read(instr.rs1())
                                            << (instr.uimm()));
            break;
          }
          default:
            throw std::runtime_error(
                "Unsupported funct7 for opcode 0010011 funct3 001");
        }
        break;
      }
      case 0b010: {  // slti rd, rs1, imm
        registers.write(instr.rd(),
                        static_cast<int32_t>(registers.read(instr.rs1())
                                             < static_cast<int32_t>(
                                                 instr.sign_extended_imm_i())));
        break;
      }
      case 0b011: {  // sltiu rd, rs1, imm
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        < instr.sign_extended_imm_i());
        break;
      }
      case 0b100: {  // xori rd, rs1, imm
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        ^ instr.sign_extended_imm_i());
        break;
      }
      case 0b101: {
        switch (instr.funct7()) {
          case 0b0000000: {  // srli rd, rs1, uimm
            registers.write(instr.rd(),
                            registers.read(instr.rs1()) >> (instr.uimm()));
            break;
          }
          case 0b0100000: {  // srai rd, rs1, uimm
            registers.write(instr.rd(),
                            static_cast<int32_t>(registers.read(instr.rs1()))
                                >> (instr.uimm()));
            break;
          }
          default:
            throw std::runtime_error(
                "Unsupported funct7 for opcode 0010011 funct3 101");
        }
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 0010011");
    }
  }
}  // namespace rvcpp