#include <rvcpp/cpu.h>

namespace rvcpp {
  void CPU::opcode_1100111(const Instruction& instr) {
    registers.next_pc
        = registers.read(instr.rs1()) + instr.sign_extended_imm_i();
    registers.write(instr.rd(), registers.pc + 4);
  }
}  // namespace rvcpp