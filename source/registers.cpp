#include <rvcpp/registers.h>

namespace rvcpp {
  Registers::Registers(Register _pc, Register sp, Register gp) : x{}, pc(_pc) {
    this->sp() = sp;
    this->gp() = gp;  // SP
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

  Register& Registers::zero() {
    x[0] = 0;  // manually enforce x0 is always zero
    return x[0];
  }
  Register& Registers::ra() { return x[1]; }
  Register& Registers::sp() { return x[2]; }
  Register& Registers::gp() { return x[3]; }
  Register& Registers::tp() { return x[4]; }
  Register& Registers::t0() { return x[5]; }
  Register& Registers::t1() { return x[6]; }
  Register& Registers::t2() { return x[7]; }
  Register& Registers::s0() { return x[8]; }
  Register& Registers::fp() { return x[8]; }
  Register& Registers::s1() { return x[9]; }
  Register& Registers::a0() { return x[10]; }
  Register& Registers::a1() { return x[11]; }
  Register& Registers::a2() { return x[12]; }
  Register& Registers::a3() { return x[13]; }
  Register& Registers::a4() { return x[14]; }
  Register& Registers::a5() { return x[15]; }
  Register& Registers::a6() { return x[16]; }
  Register& Registers::a7() { return x[17]; }
  Register& Registers::s2() { return x[18]; }
  Register& Registers::s3() { return x[19]; }
  Register& Registers::s4() { return x[20]; }
  Register& Registers::s5() { return x[21]; }
  Register& Registers::s6() { return x[22]; }
  Register& Registers::s7() { return x[23]; }
  Register& Registers::s8() { return x[24]; }
  Register& Registers::s9() { return x[25]; }
  Register& Registers::s10() { return x[26]; }
  Register& Registers::s11() { return x[27]; }
  Register& Registers::t3() { return x[28]; }
  Register& Registers::t4() { return x[29]; }
  Register& Registers::t5() { return x[30]; }
  Register& Registers::t6() { return x[31]; }
}  // namespace rvcpp