#include "List.hh"

#include <catch2/catch.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

TEST_CASE("List") {
  Lab2::List<int> list;
  REQUIRE(list.empty());
  REQUIRE(list.length() == 0);

  SECTION("with init list") {
    Lab2::List list{1, 2, 3, 4};
    REQUIRE(list.length() == 4);
    for (int i = 1; i < 5; i++) {
      REQUIRE(list.get(i) == i);
    }
  }
}

TEST_CASE("insert") {
  Lab2::List<int> list;
  list.insert(1);
  REQUIRE(list.empty() == false);
  REQUIRE(list.length() == 1);

  list.insert(2);

  REQUIRE(list.length() == 2);
  SECTION("with index") {
    Lab2::List<int> list{1, 2, 3};
    list.insert(1, 999);
    // {1, 999, 2, 3}
    REQUIRE(list.length() == 4);
    REQUIRE(list.get(1) == 1);
    REQUIRE(list.get(2) == 999);
    REQUIRE(list.get(3) == 2);
    REQUIRE(list.get(4) == 3);
    Lab2::List<int> list2{1, 999, 2, 3};
    REQUIRE(list == list2);
  }
}

TEST_CASE("get") {
  Lab2::List<int> list{1, 9, 8, 3};
  REQUIRE_THROWS_AS(list.get(0), std::underflow_error);
  REQUIRE_THROWS_AS(list.get(10000), std::overflow_error);

  REQUIRE(list.length() == 4);
  REQUIRE(list.get(2) == 9);
}

TEST_CASE("locate") {
  Lab2::List<int> list{1, 3, 5, 7, 9, 10};
  REQUIRE(list.length() == 6);

  REQUIRE(list.locate(3, [](const int &a, const int &b) { return a == b; }) == 2);
  REQUIRE(list.locate(7, [](const int &a, const int &b) { return a == b; }) == 4);
  REQUIRE(list.locate(10, [](const int &a, const int &b) { return a == b; }) == 6);
}

TEST_CASE("elem operations") {
  Lab2::List<std::string> list{"aaa", "bbb", "ccc", "ddd"};
  REQUIRE(list.length() == 4);
  SECTION("prior") {
    REQUIRE(list.prior("bbb") == "aaa");
    REQUIRE(list.prior("ddd") == "ccc");
    REQUIRE(list.prior("ccc") == "bbb");
    REQUIRE_THROWS_AS(list.prior("aaa"), std::runtime_error);
  }

  SECTION("next") {
    REQUIRE(list.next("aaa") == "bbb");
    REQUIRE(list.next("bbb") == "ccc");
    REQUIRE_THROWS_AS(list.next("ddd"), std::runtime_error);
  }
}

TEST_CASE("traverse") {
  Lab2::List<int> list{1, 2, 3, 4, 5, 6};
  REQUIRE(list.length() == 6);

  list.traverse([](int &x) { x *= 2; });

  REQUIRE(list.get(1) == 2);
  REQUIRE(list.get(2) == 4);
  REQUIRE(list.get(3) == 6);
  REQUIRE(list.get(4) == 8);
  REQUIRE(list.get(5) == 10);
  REQUIRE(list.get(6) == 12);

  const Lab2::List<int> result{2, 4, 6, 8, 10, 12};
  REQUIRE(list == result);
}

TEST_CASE("remove") {
  Lab2::List<std::string> list{"aaa", "bbb", "ccc", "ddd"};
  REQUIRE(list.length() == 4);
  // remove from head
  list.remove(1);
  // {"bbb", "ccc", "ddd"}
  REQUIRE(list.length() == 3);
  const Lab2::List<std::string> result{"bbb", "ccc", "ddd"};
  REQUIRE(list == result);

  // remove from tail
  list.remove(list.length());
  const Lab2::List<std::string> result2{"bbb", "ccc"};
  REQUIRE(list == result2);
}
