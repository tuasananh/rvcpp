#pragma once
#include <cstdint>

namespace rvcpp {
  static constexpr uint32_t mask(uint32_t bits) { return (1u << bits) - 1; }
}  // namespace rvcpp