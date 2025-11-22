#include <rvcpp/cpu.h>

namespace rvcpp {
  // Load upper immediate
  void CPU::opcode_0110111(const Instruction& instr) {
    registers.write(instr.rd(), instr.shifted_upimm());
  }
}  // namespace rvcpp