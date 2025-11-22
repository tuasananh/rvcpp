#include <rvcpp/cpu.h>
#include <rvcpp/helper.h>

namespace rvcpp {
  // Load instructions
  void CPU::opcode_0110011(const Instruction& instr) {
    switch (instr.funct3()) {
      case 0b000: {
        switch (instr.funct7()) {
          case 0b0000000: {  // add rd, rs1, rs2
            registers.write(instr.rd(), registers.read(instr.rs1())
                                            + registers.read(instr.rs2()));
            break;
          }
          case 0b0100000: {  // sub rd, rs1, rs2
            registers.write(instr.rd(), registers.read(instr.rs1())
                                            - registers.read(instr.rs2()));
            break;
          }
          default:
            throw std::runtime_error(
                "Unsupported funct7 for opcode 0110011 funct3 000");
        }
        break;
      }
      case 0b001: {  // sll rd, rs1, rs2
        registers.write(instr.rd(),
                        registers.read(instr.rs1())
                            << (registers.read(instr.rs2()) & mask(5)));
        break;
      }
      case 0b010: {  // slt rd, rs1, rs2
        registers.write(instr.rd(),
                        static_cast<int32_t>(registers.read(instr.rs1())
                                             < static_cast<int32_t>(
                                                 registers.read(instr.rs2()))));
        break;
      }
      case 0b011: {  // sltu rd, rs1, rs2
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        < registers.read(instr.rs2()));
        break;
      }
      case 0b100: {  // xor rd, rs1, rs2
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        ^ registers.read(instr.rs2()));
        break;
      }
      case 0b101: {
        switch (instr.funct7()) {
          case 0b0000000: {  // srl rd, rs1, rs2
            registers.write(instr.rd(),
                            registers.read(instr.rs1())
                                >> (registers.read(instr.rs2()) & mask(5)));
            break;
          }
          case 0b0100000: {  // sra rd, rs1, rs2
            registers.write(instr.rd(),
                            static_cast<int32_t>(registers.read(instr.rs1()))
                                >> (registers.read(instr.rs2()) & mask(5)));
            break;
          }
          default:
            throw std::runtime_error(
                "Unsupported funct7 for opcode 0110011 funct3 101");
        }
        break;
      }
      case 0b110: {  // or rd, rs1, rs2
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        | registers.read(instr.rs2()));
        break;
      }
      case 0b111: {  // and rd, rs1, rs2
        registers.write(instr.rd(), registers.read(instr.rs1())
                                        & registers.read(instr.rs2()));
        break;
      }
      default:
        throw std::runtime_error("Unsupported funct3 for opcode 0110011");
    }
  }
}  // namespace rvcpp