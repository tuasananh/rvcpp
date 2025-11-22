#include <rvcpp/cpu.h>
#include <string>

namespace rvcpp {
  // Load instructions
  void CPU::opcode_not_implemented(const Instruction& instr) {
    throw std::runtime_error(
        "Opcode not implemented: " + std::to_string(instr.op()));
  }
}  // namespace rvcpp