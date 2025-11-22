#pragma once

#include <array>

namespace rvcpp {
  using Register = uint32_t;

  class Registers {
    std::array<Register, 32> x;

  public:
    Register pc;

    Registers(Register pc, Register sp, Register gp);

    Register read(size_t index) const;
    void write(size_t index, Register value);
  };
}  // namespace rvcpp