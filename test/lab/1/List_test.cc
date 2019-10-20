#include "List.hh"

#include <catch2/catch.hpp>

TEST_CASE("init seq list") {
  SECTION("operator[]") {
    Lab1::List<std::string> list(10);
    const auto magicStr = "magic";
    list[0] = magicStr;
    REQUIRE(list[0] == magicStr);
  }

  SECTION("empty") {
    Lab1::List<std::string> list;
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }

  SECTION("with size") {
    const auto size = 10;
    const auto magicNumber = 1.78;
    Lab1::List<double> list(size);
    REQUIRE(list.size() == 10);
    for (int i = 0; i < size; i++) {
      list[i] = magicNumber;
      REQUIRE(list[i] == magicNumber);
    }
  }

  SECTION("init list") {
    Lab1::List<int> l{1, 2, 3};
    REQUIRE(l.size() == 6);
    REQUIRE(l.length() == 3);
    REQUIRE(l[1] == 2);
  }
}

TEST_CASE("traversse") {
  auto l = Lab1::List<int>{1, 2, 3, 4};
  REQUIRE(l.length() == 4);
  REQUIRE(l.size() == 8);
  const auto times = 2;
  l.traverse([times](int& x) { x *= times; });
  REQUIRE(l.get(0) == 2);
  REQUIRE(l.get(1) == 4);
  REQUIRE(l.get(2) == 6);
  REQUIRE(l.get(3) == 8);
}
