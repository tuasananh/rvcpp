# RISC-V C++

## Project Roadmap: 1-Month RISC-V Simulator & Assembler

This roadmap aims to build a functional RV32I (32-bit Integer) simulator and a basic assembler in C++ within 4 weeks.

### Week 1: Foundation & Core Architecture
**Goal:** Establish the project structure and implement the basic CPU state and instruction decoding.

- [ ] **Day 1-2: Project Setup, Machine & Memory**
    - Set up CMake project structure.
    - Define `Memory` class: Byte-addressable memory (start with 64KB RAM).
    - Define `Cpu` class: Holds state (32 registers, PC) and performs execution.
    - Define `Machine` class: Top-level container that initializes `Memory` with a binary file and sets up the `Cpu`.
    - Implement `Memory::read<T>(addr)`:
        - Template function to read `uint8_t`, `uint16_t`, `uint32_t`.
        - Returns `std::expected<T, MemoryError>` to handle out-of-bounds access safely (C++23).
    - Implement `Memory::write<T>(addr, value)`:
        - Template function to write data to memory.
        - Returns `std::expected<void, MemoryError>`.
- [ ] **Day 3-4: Instruction Fetch & Decode**
    - Implement `fetch()`: Read 32-bit instruction from memory at `pc`.
    - Implement `decode()`: Extract fields (opcode, rd, rs1, rs2, funct3, funct7, imm) based on instruction types (R, I, S, B, U, J).
    - Create a helper to sign-extend immediates.
- [ ] **Day 5-7: Basic Execution (R-Type)**
    - Implement the execution loop: Fetch -> Decode -> Execute -> Writeback.
    - Implement R-Type instructions: `ADD`, `SUB`, `AND`, `OR`, `XOR`, `SLL`, `SRL`, `SRA`.
    - Unit test: Execute hardcoded binary instructions and verify register changes.

### Week 2: Completing RV32I & Control Flow
**Goal:** Implement the full Base Integer Instruction Set (RV32I) and handle branching.

- [ ] **Day 8-10: Immediate & Memory Instructions (I-Type, S-Type)**
    - Implement I-Type arithmetic: `ADDI`, `ANDI`, `ORI`, `XORI`, `SLTI`, `SLTIU`.
    - Implement Loads: `LB`, `LH`, `LW`, `LBU`, `LHU`.
    - Implement Stores: `SB`, `SH`, `SW`.
- [ ] **Day 11-12: Control Flow (B-Type, J-Type)**
    - Implement Branches: `BEQ`, `BNE`, `BLT`, `BGE`, `BLTU`, `BGEU`.
    - Implement Jumps: `JAL`, `JALR`.
    - Ensure `pc` updates correctly (relative vs absolute addressing).
- [ ] **Day 13-14: Upper Immediates & System**
    - Implement `LUI` (Load Upper Immediate) and `AUIPC`.
    - Implement basic `ECALL` handling (initially just for stopping execution).

### Week 3: The Assembler
**Goal:** Convert assembly text files into binary machine code that the simulator can run.

- [ ] **Day 15-17: Parsing & Tokenization**
    - Create a `Parser` to read `.asm` files line by line.
    - Tokenize lines (e.g., `add x1, x2, x3` -> `[Instruction: add, Reg: x1, Reg: x2, Reg: x3]`).
    - Handle comments and whitespace.
- [ ] **Day 18-19: Label Handling & Two-Pass Assembly**
    - **Pass 1:** Scan for labels (e.g., `loop:`) and record their addresses in a symbol table.
    - **Pass 2:** Generate machine code, resolving label references to relative offsets.
- [ ] **Day 20-21: Code Generation**
    - Implement binary encoding for all supported RV32I instructions.
    - Support basic pseudo-instructions (e.g., `li` -> `lui` + `addi`, `mv` -> `addi`).
    - Output a raw binary buffer or file.

### Week 4: Integration, System Calls & Testing
**Goal:** Connect the assembler and simulator, support I/O, and run complex programs.

- [ ] **Day 22-24: Integration**
    - Connect the Assembler's output to the `Machine` class for immediate execution.
    - Create a CLI driver (e.g., `./rvcpp run program.asm`) that assembles source code and runs the resulting binary using `Machine`.
- [ ] **Day 25-26: System Calls (I/O)**
    - Implement `ECALL` handlers for basic Linux syscalls:
        - `print_int` / `print_string` (write to stdout).
        - `exit` (terminate simulation).
- [ ] **Day 27-28: Complex Programs**
    - Write and test "Fibonacci Sequence" in assembly.
    - Write and test "Factorial" in assembly.
    - Debug any edge cases in branching or memory access.
- [ ] **Day 29-30: Polish & Documentation**
    - Add CLI flags (e.g., `--debug` to print registers after every step).
    - Finalize README and code comments.

