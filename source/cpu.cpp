#include <rvcpp/cpu.h>

#include <bitset>
#include <iostream>
#include <functional>

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
    opcode_handlers[0b0100011] = &CPU::opcode_0100011;
    opcode_handlers[0b0110011] = &CPU::opcode_0110011;
    opcode_handlers[0b0110111] = &CPU::opcode_0110111;
    opcode_handlers[0b1100011] = &CPU::opcode_1100011;
    opcode_handlers[0b1100111] = &CPU::opcode_1100111;
    opcode_handlers[0b1101111] = &CPU::opcode_1101111;
  }

  Instruction CPU::fetch_instruction() {
    Instruction instr = memory.read<uint32_t>(registers.pc);
    return instr;
  }

  void CPU::execute_instruction(const Instruction& instr) {
    // weird c++ syntax be like
    // (this->*(opcode_handlers[instr.op()]))(instr);
    // i prefer this tbh
    registers.next_pc = registers.pc + 4;
    std::invoke(opcode_handlers[instr.op()], this, instr);
    registers.pc = registers.next_pc;
  }

  void CPU::simulate() {
    while (true) {
      auto instr = fetch_instruction();
      execute_instruction(instr);
    }
  }

  void CPU::simulate(size_t instruction_limit) {
    size_t executed_instructions = 0;
    while (executed_instructions < instruction_limit) {
      auto instr = fetch_instruction();
      execute_instruction(instr);
      executed_instructions++;
    }
  }

  Register CPU::read_register(size_t index) const {
    return registers.read(index);
  }

  Register CPU::read_pc() const { return registers.pc; }
}  // namespace rvcpp