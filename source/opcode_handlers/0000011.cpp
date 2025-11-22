#include <rvcpp/cpu.h>

#include <iostream>

namespace rvcpp {
  void CPU::opcode_0000011(const Instruction& instr) {
#ifdef _DEBUG
    std::cerr << "Executing opcode 0000011 (Load)\n";
#endif
    // Load instructions
    uint32_t addr = registers.read(instr.rs1()) + instr.sign_extended_imm_i();
    switch (instr.funct3()) {
      case 0b000: {  // lb rd, imm(rs1)
        registers.write(instr.rd(),
                        static_cast<uint32_t>(memory.read<int8_t>(addr)));
        break;
      }
      case 0b001: {  // lh rd, imm(rs1)
        registers.write(instr.rd(),
                        static_cast<uint32_t>(memory.read<int16_t>(addr)));
        break;
      }
      case 0b010: {  // lw rd, imm(rs1)
        registers.write(instr.rd(), (memory.read<uint32_t>(addr)));
        break;
      }
      case 0b100: {  // lbu rd, imm(rs1)
        registers.write(instr.rd(),
                        static_cast<uint32_t>(memory.read<uint8_t>(addr)));
        break;
      }
      case 0b101: {  // lhu rd, imm(rs1)
        registers.write(instr.rd(),
                        static_cast<uint32_t>(memory.read<uint16_t>(addr)));
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 0000011");
    }
  }
}  // namespace rvcpp