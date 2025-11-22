#include <rvcpp/registers.h>

namespace rvcpp {
  Registers::Registers(Register _pc, Register sp, Register gp) : x{}, pc(_pc) {
    constexpr size_t SP_REGISTER = 2;
    constexpr size_t GP_REGISTER = 3;
    this->x[SP_REGISTER] = sp;  // SP
    this->x[GP_REGISTER] = gp;  // GP
  }

  Register Registers::read(size_t index) const {
    if (index == 0) {
      return 0;  // x0 is always zero
    }
    return x.at(index);
  }

  void Registers::write(size_t index, Register value) {
    if (index == 0) {
      return;  // x0 is always zero
    }
    x.at(index) = value;
  }
}  // namespace rvcpp