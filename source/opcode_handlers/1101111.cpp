#include <rvcpp/cpu.h>

namespace rvcpp {
  void CPU::opcode_1101111(const Instruction& instr) {
    registers.next_pc = instr.jump_target_address(registers.pc);
    registers.write(instr.rd(), registers.pc + 4);
  }
}  // namespace rvcpp