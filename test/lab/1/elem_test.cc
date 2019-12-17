#include <catch2/catch.hpp>

#include "List.hh"

TEST_CASE("elem") {
  const auto s1 = "aaa";
  const auto s2 = "bbb";
  const auto s3 = "ccc";
  const auto s4 = "ddd";
  const auto s5 = "eee";
  Lab1::List<std::string> l{s1, s2, s3, s4, s5};
  REQUIRE(l.size() == 10);

  SECTION("get") {
    REQUIRE(l.get(0) == s1);
    REQUIRE(l.get(1) == s2);
    REQUIRE(l.get(3) == s4);
    REQUIRE_THROWS_AS(l.get(10), std::overflow_error);
    REQUIRE_THROWS_AS(l.get(-1), std::overflow_error);
    REQUIRE_THROWS_AS(l[-1], std::overflow_error);

  }

  SECTION("locate") {
    REQUIRE(0 == l.locate(s1, [](const std::string& a, const std::string& b) { return a == b; }));
    REQUIRE(4 == l.locate(s5, [](const std::string& a, const std::string& b) { return a == b; }));
    REQUIRE(-1 == l.locate("1", [](const std::string& a, const std::string& b) { return a == b; }));
  }

  SECTION("prior") {
    REQUIRE_THROWS_AS(l.prior(s1), std::underflow_error);
    REQUIRE(l.prior(s4) == s3);
    REQUIRE_THROWS_AS(l.prior("sss"),std::runtime_error);
  }

  SECTION("next") {
    REQUIRE_THROWS_AS(l.next(s5), std::overflow_error);
    REQUIRE_THROWS_AS(l.next("sss"),std::runtime_error);
    REQUIRE(s3 == l.next(s2));
  }
}
