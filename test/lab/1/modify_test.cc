#include <catch2/catch.hpp>

#include "List.hh"

TEST_CASE("modify") {
  Lab1::List<std::string> l{"aaa", "bbb", "ccc"};

  REQUIRE(l.size() == 6);
  REQUIRE(l.length() == 3);
  SECTION("insert to head") {
    l.insert(1, "sss");
    REQUIRE(l[0] == "sss");
    REQUIRE(l.length() == 4);
  }

  SECTION("insert to tail") {
    l.insert(l.length() + 1, "bbb");
    REQUIRE(l[l.length() - 1] == "bbb");
    REQUIRE(l.length() == 4);
  }

  SECTION("delete from head") {
    l.remove(1);
    REQUIRE(l.length() == 2);
    REQUIRE(l[0] == "bbb");
  }

  SECTION("delete using reference") {
    std::string out;
    l.remove(1, out);
    REQUIRE(l.length() == 2);
    REQUIRE(out == "aaa");
  }

  SECTION("delete from tail") {
    l.remove(l.length());
    REQUIRE(l.length() == 2);
    REQUIRE(l[l.length() - 1] == "bbb");
  }
}
