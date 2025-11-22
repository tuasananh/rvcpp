#pragma once

#include <rvcpp/instruction.h>
#include <rvcpp/memory.h>
#include <rvcpp/registers.h>

#include <array>

namespace rvcpp {
  class CPU {
    Memory& memory;
    Registers registers;

    using Handler = void (CPU::*)(const Instruction& instr);
    std::array<Handler, 128> opcode_handlers;

    Instruction fetch_instruction();
    void execute_instruction(const Instruction& instr);

    // Load instructions
    void opcode_0000011(const Instruction& instr);
    // Immediate arithmetic instructions
    void opcode_0010011(const Instruction& instr);
    // Add upper immediate to PC
    void opcode_0010111(const Instruction& instr);
    // Register arithmetic instructions
    void opcode_0110011(const Instruction& instr);
    // Load upper immediate
    void opcode_0110111(const Instruction& instr);
    // Branch instructions
    void opcode_1100011(const Instruction& instr);
    // Jump and link register
    void opcode_1100111(const Instruction& instr);
    // Jump and link
    void opcode_1101111(const Instruction& instr);

    // Fallback for unimplemented opcodes
    void opcode_not_implemented(const Instruction& instr);

  public:
    CPU(Memory& memory);

    void simulate();
  };
}  // namespace rvcpp