#include <rvcpp/cpu.h>

namespace rvcpp {
  void CPU::opcode_1100011(const Instruction& instr) {
    switch (instr.funct3()) {
      case 0b000: {  // beq rs1, rs2, imm
        if (registers.read(instr.rs1()) == registers.read(instr.rs2())) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      case 0b001: {  // bne rs1, rs2, imm
        if (registers.read(instr.rs1()) != registers.read(instr.rs2())) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      case 0b100: {  // blt rs1, rs2, imm
        if (static_cast<int32_t>(registers.read(instr.rs1()))
            < static_cast<int32_t>(registers.read(instr.rs2()))) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      case 0b101: {  // bge rs1, rs2, imm
        if (static_cast<int32_t>(registers.read(instr.rs1()))
            >= static_cast<int32_t>(registers.read(instr.rs2()))) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      case 0b110: {  // bltu rs1, rs2, imm
        if (registers.read(instr.rs1()) < registers.read(instr.rs2())) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      case 0b111: {  // bgeu rs1, rs2, imm
        if (registers.read(instr.rs1()) >= registers.read(instr.rs2())) {
          registers.next_pc = instr.branch_target_address(registers.pc);
        }
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 1100011");
    }
  }
}  // namespace rvcpp