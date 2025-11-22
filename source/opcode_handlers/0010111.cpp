#include <rvcpp/cpu.h>

namespace rvcpp {
  // Add upper immediate to PC
  void CPU::opcode_0010111(const Instruction& instr) {
    registers.write(instr.rd(), registers.pc + instr.shifted_upimm());
  }
}  // namespace rvcpp