#include "List.hh"

#include <catch2/catch.hpp>

TEST_CASE("List") {
  Lab2::List<int> list;
  REQUIRE(list.empty());
  REQUIRE(list.length() == 0);
}

TEST_CASE("insert") {
  Lab2::List<int> list;
  list.insert(1);
  REQUIRE(list.empty() == false);
  REQUIRE(list.length() == 1);

  list.insert(2);

  REQUIRE(list.length() == 2);
}
