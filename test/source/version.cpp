#include <doctest/doctest.h>
#include <rvcpp/version.h>

#include <string>

TEST_CASE("rvcpp version") {
  static_assert(std::string_view(RVCPP_VERSION) == std::string_view("1.0"));
  CHECK(std::string(RVCPP_VERSION) == std::string("1.0"));
}