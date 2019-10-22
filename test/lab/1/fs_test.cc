#include <catch2/catch.hpp>
#include <iostream>

#include "List.hh"

TEST_CASE("fs") {
  Lab1::List<std::string> list{"aaa", "bbb", "ccc", "ddd"};
  list.insert(3, "000");
  list.save("./list.dat");

  Lab1::List<std::string> listIn;
  listIn.load("./list.dat");

  REQUIRE(list.length() == listIn.length());

  for (size_t i = 0; i < list.length(); i++) {
    REQUIRE(list[i] == listIn[i]);
  }
}