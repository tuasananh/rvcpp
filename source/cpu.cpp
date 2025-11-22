#include <rvcpp/cpu.h>

#include <bitset>
#include <iostream>

namespace rvcpp {
  CPU::CPU(Memory& memory_)
      : memory(memory_),
        registers(memory.get_initial_program_counter(),
                  memory.get_initial_stack_pointer(),
                  memory.get_initial_global_pointer()) {
    opcode_handlers.fill(&CPU::opcode_not_implemented);
    opcode_handlers[0b0000011] = &CPU::opcode_0000011;
    opcode_handlers[0b0010011] = &CPU::opcode_0010011;
    opcode_handlers[0b0010111] = &CPU::opcode_0010111;
    opcode_handlers[0b0110011] = &CPU::opcode_0110011;
    opcode_handlers[0b0110111] = &CPU::opcode_0110111;
    opcode_handlers[0b1100011] = &CPU::opcode_1100011;
    opcode_handlers[0b1100111] = &CPU::opcode_1100111;
    opcode_handlers[0b1101111] = &CPU::opcode_1101111;
  }

  Instruction CPU::fetch_instruction() {
    Instruction instr = memory.read<uint32_t>(registers.pc);
    registers.pc += 4;  // Advance PC
    return instr;
  }

  void CPU::execute_instruction(const Instruction& instr) {
    // weird c++ syntax be like
    // (this->*(opcode_handlers[instr.op()]))(instr);
    // i prefer this tbh
    std::invoke(opcode_handlers[instr.op()], this, instr);
  }

  void CPU::simulate() {
// Simulation logic goes here
#ifdef _DEBUG
    int instr_cap = 100;
    int instr_count = 0;
#endif
    while (true) {
      auto instr = fetch_instruction();

#ifdef _DEBUG
      instr_count++;
      std::cerr << "Instr: " << instr_count << " PC: " << std::hex
                << registers.pc << std::dec << "\n";
      std::cerr << "Current instr: op=" << std::bitset<7>(instr.op())
                << " rd=" << std::bitset<5>(instr.rd())
                << " funct3=" << std::bitset<3>(instr.funct3())
                << " rs1=" << std::bitset<5>(instr.rs1())
                << " rs2=" << std::bitset<5>(instr.rs2())
                << " funct7=" << std::bitset<7>(instr.funct7())
                << " se_imm_i=" << std::bitset<32>(instr.sign_extended_imm_i())
                << "\n";
#endif

      execute_instruction(instr);

#ifdef _DEBUG
      if (instr_count >= instr_cap) {
        std::cerr << "Reached instruction cap of " << instr_cap
                  << ", stopping simulation.\n";
        break;
      }
#endif
    }
  }
}  // namespace rvcpp