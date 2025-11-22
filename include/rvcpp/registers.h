#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace rvcpp {
  using Register = uint32_t;

  class Registers {
    std::array<Register, 32> x;

  public:
    Register pc;
    Register next_pc;

    Registers(Register pc, Register sp, Register gp);

    Register read(size_t index) const;
    void write(size_t index, Register value);
  };
}  // namespace rvcpp