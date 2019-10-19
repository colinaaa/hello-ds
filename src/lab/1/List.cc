#include "List.hh"

template <typename T>
Lab1::List<T>::List() : length(0), size(0), elem(std::make_unique<T[]>(0)) {}

template <typename T>
Lab1::List<T>::List(int length)
    : length(length), size(length), elem(std::make_unique<T[]>(length)) {
  // see:
  // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
}

template <typename T>
auto Lab1::List<T>::operator[](uint index) -> T& {
  // TODO(colinaaa): throw error when overflow
  return elem[index];
}

template <typename T>
auto Lab1::List<T>::empty() {
  return length == 0;
}

#include <catch2/catch.hpp>
#include <iostream>
TEST_CASE("init seq list") {
  SECTION("operator[]") {
    Lab1::List<std::string> list(10);
    const auto magicStr = "magic";
    list[0] = magicStr;
    REQUIRE(list[0] == magicStr);
  }

  SECTION("empty") {
    Lab1::List<std::string> list;
    REQUIRE(list.getSize() == 0);
    REQUIRE(list.empty());
  }

  SECTION("with size") {
    const auto size = 10;
    const auto magicNumber = 1.78;
    Lab1::List<double> list(size);
    REQUIRE(list.getSize() == 10);
    for (int i = 0; i < size; i++) {
      list[i] = magicNumber;
      REQUIRE(list[i] == magicNumber);
    }
  }
}