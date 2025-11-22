#pragma once

#include <rvcpp/cpu.h>
#include <rvcpp/memory.h>

namespace rvcpp {
  class Machine {
    CPU cpu;
    Memory memory;

  public:
    Machine(const std::vector<std::byte>& program);

    void simulate();
  };
}  // namespace rvcpp