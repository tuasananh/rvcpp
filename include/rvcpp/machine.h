#pragma once

#include <rvcpp/cpu.h>
#include <rvcpp/memory.h>

namespace rvcpp {
  class Machine {
    Memory memory;
    CPU cpu;

  public:
    Machine(const std::vector<std::byte>& program);

    void simulate();
  };
}  // namespace rvcpp