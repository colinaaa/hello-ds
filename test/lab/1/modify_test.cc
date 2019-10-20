#include <catch2/catch.hpp>

#include "List.hh"

TEST_CASE("modify") {
  Lab1::List<std::string> l{"aaa", "bbb", "ccc"};

  REQUIRE(l.size() == 6);
  REQUIRE(l.length() == 3);
  SECTION("resize") {
    l.resize(10);
    REQUIRE(l.size() == 10);
    REQUIRE(l.length() == 3);
    REQUIRE_THROWS_AS(l.resize(2), std::length_error);
  }

  SECTION("insert") {
    l.insert(1, "sss");
    REQUIRE(l[0] == "sss");
    REQUIRE(l.length() == 4);

    l.insert(l.length() + 1, "bbb");
    REQUIRE(l[l.length() - 1] == "bbb");
    REQUIRE(l.length() == 5);

    REQUIRE_THROWS_AS(l.insert(0, "11"), std::underflow_error);
    REQUIRE_THROWS_AS(l.insert(100, "22"), std::overflow_error);
  }

  SECTION("delete from head") {
    l.remove(1);
    REQUIRE(l.length() == 2);
    REQUIRE(l[0] == "bbb");

    REQUIRE_THROWS_AS(l.remove(0), std::underflow_error);
    REQUIRE_THROWS_AS(l.remove(100), std::overflow_error);
  }

  SECTION("delete using reference") {
    std::string out;
    l.remove(1, out);
    REQUIRE(l.length() == 2);
    REQUIRE(out == "aaa");

    REQUIRE_THROWS_AS(l.remove(0, out), std::underflow_error);
    REQUIRE_THROWS_AS(l.remove(100, out), std::overflow_error);
  }

  SECTION("delete from tail") {
    l.remove(l.length());
    REQUIRE(l.length() == 2);
    REQUIRE(l[l.length() - 1] == "bbb");
  }
}
