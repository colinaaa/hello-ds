#include <gsl/gsl>

auto main() -> int { return 0; }

#include <catch2/catch.hpp>
TEST_CASE("foo") {
  REQUIRE(1 == 1);
  REQUIRE_FALSE(1 == 2);
}