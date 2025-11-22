#include <rvcpp/cpu.h>
#include <rvcpp/helper.h>

#include <iostream>

namespace rvcpp {
  void CPU::opcode_0100011(const Instruction& instr) {
    uint32_t addr = registers.read(instr.rs1()) + instr.sign_extended_imm_s();
    switch (instr.funct3()) {
      case 0b000: {  // SB
        auto value
            = static_cast<uint8_t>(registers.read(instr.rs2()) & mask(8));
        memory.write(addr, value);
        break;
      }
      case 0b001: {  // SH
        auto value
            = static_cast<uint16_t>(registers.read(instr.rs2()) & mask(16));
        memory.write(addr, value);
        break;
      }
      case 0b010: {  // SW
        auto value = registers.read(instr.rs2());
        memory.write(addr, value);
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 0100011");
    }
  }
}  // namespace rvcpp