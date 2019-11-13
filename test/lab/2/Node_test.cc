#include "Node.hh"

#include <catch2/catch.hpp>
TEST_CASE("Node2") {
  SECTION("default init") {
    Lab2::Node<int> n;
    REQUIRE(nullptr == n.next());
    REQUIRE(n.data() == int());
  }
}
