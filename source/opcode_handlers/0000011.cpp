#include <rvcpp/cpu.h>
#include <iostream>

namespace rvcpp {
  void CPU::opcode_0000011(const Instruction& instr) {
    #ifdef _DEBUG
    std::cerr << "Executing opcode 0000011 (Load)\n";
    #endif
    // Load instructions
    switch (instr.funct3()) {
      case 0b010: {  // LW
        uint32_t addr = registers.read(instr.rs1()) + instr.sign_extended_imm_i();
        registers.write(instr.rd(), memory.read<uint32_t>(addr));
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 0000011");
    }
  }
}