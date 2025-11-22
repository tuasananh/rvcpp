#include <rvcpp/machine.h>

#include <stdexcept>

namespace rvcpp {
  Machine::Machine(const std::vector<std::byte>& program)
      : memory(), cpu(memory) {
    // Load this program into memory's text segment

    // Right now no data yet, all this program is text
    if (program.size() > Memory::get_text_size()) {
      throw std::runtime_error("Program size exceeds text segment size");
    }

    uint32_t text_start = Memory::get_initial_program_counter();
    for (size_t i = 0; i < program.size(); ++i) {
      memory.write(text_start + i, program[i]);
    }
  }

  void Machine::simulate() { cpu.simulate(); }
}  // namespace rvcpp