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

    Register& zero();
    Register& ra();
    Register& sp();
    Register& gp();
    Register& tp();
    Register& t0();
    Register& t1();
    Register& t2();
    Register& s0();
    Register& fp();
    Register& s1();
    Register& a0();
    Register& a1();
    Register& a2();
    Register& a3();
    Register& a4();
    Register& a5();
    Register& a6();
    Register& a7();
    Register& s2();
    Register& s3();
    Register& s4();
    Register& s5();
    Register& s6();
    Register& s7();
    Register& s8();
    Register& s9();
    Register& s10();
    Register& s11();
    Register& t3();
    Register& t4();
    Register& t5();
    Register& t6();
  };
}  // namespace rvcpp