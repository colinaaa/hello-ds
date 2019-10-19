#include "List.hh"
// #define CATCH_CONFIG_MAIN
// #include<catch2/catch.hpp>
#include <catch2/catch.hpp>
#include <initializer_list>

template <typename T>
Lab1::List<T>::List() : _length(0), _size(0), _elem(std::make_unique<T[]>(0)) {}

template <typename T>
Lab1::List<T>::List(int size) : _length(0), _size(size), _elem(std::make_unique<T[]>(size)) {
  // see:
  // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
}

template <typename T>
Lab1::List<T>::List(std::initializer_list<T> ilist)
    : _length(ilist.size()), _size(ilist.size()), _elem(std::make_unique<T[]>(_size)) {
  for (auto iter = ilist.begin(); iter != ilist.end(); iter++) {
    _elem[iter - ilist.begin()] = *iter;
  }
}

template <typename T>
auto Lab1::List<T>::operator[](uint index) -> T& {
  // TODO(colinaaa): throw error when overflow
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::empty() -> bool {
  return _length == 0;
}

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
    REQUIRE(l.size() == 3);
    REQUIRE(l.length() == 3);
    REQUIRE(l[1] == 2);
  }
}

template <typename T>
auto Lab1::List<T>::get(int index) -> T& {
  // TODO(colinaaa): check overflow
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::locate(const T e, bool eq(const T& a, const T& b)) -> int {
  for (int i = 0; i < _length; i++) {
    if (eq(e, _elem[i])) {
      return i;
    }
  }
  return 0;
}

template <typename T>
auto Lab1::List<T>::prior(const T& e) -> T& {
  auto pos = locate(e, [](const std::string& a, const std::string& b) { return a == b; });
  // TODO(colinaaa): check whether pos == 0 or overflow
  if (pos < 0) {
    return _elem[pos];
  }
  return _elem[pos - 1];
}

template <typename T>
auto Lab1::List<T>::next(const T& e) -> T& {
  auto pos = locate(e, [](const std::string& a, const std::string& b) { return a == b; });
  // TODO(colinaaa): check whether pos == length or underflow
  if (pos == _length) {
    return _elem[pos];
  }
  return _elem[pos + 1];
}

TEST_CASE("elem") {
  const auto s1 = "aaa";
  const auto s2 = "bbb";
  const auto s3 = "ccc";
  const auto s4 = "ddd";
  const auto s5 = "eee";
  Lab1::List<std::string> l{s1, s2, s3, s4, s5};
  REQUIRE(l.size() == 5);

  SECTION("get") {
    REQUIRE(l.get(0) == s1);
    REQUIRE(l.get(1) == s2);
    REQUIRE(l.get(3) == s4);
  }

  SECTION("locate") {
    REQUIRE(0 == l.locate(s1, [](const std::string& a, const std::string& b) { return a == b; }));
    REQUIRE(4 == l.locate(s5, [](const std::string& a, const std::string& b) { return a == b; }));
  }

  SECTION("prior") { REQUIRE(l.prior(s4) == s3); }

  SECTION("next") { REQUIRE(s3 == l.next(s2)); }
}
