#include "List.hh"
// #define CATCH_CONFIG_MAIN
// #include<catch2/catch.hpp>
#include <catch2/catch.hpp>

template <typename T>
Lab1::List<T>::List() : _length(0), _size(0), _elem(std::make_unique<T[]>(0)) {}

template <typename T>
Lab1::List<T>::List(std::size_t size)
    : _length(0), _size(size), _elem(std::make_unique<T[]>(size)) {
  // see:
  // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
}

template <typename T>
Lab1::List<T>::List(std::initializer_list<T> ilist)
    : _length(ilist.size()), _size(2 * ilist.size()), _elem(std::make_unique<T[]>(2 * _size)) {
  for (auto iter = ilist.begin(); iter != ilist.end(); iter++) {
    _elem[iter - ilist.begin()] = *iter;
  }
}

template <typename T>
auto Lab1::List<T>::operator[](std::size_t index) -> T& {
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
    REQUIRE(l.size() == 6);
    REQUIRE(l.length() == 3);
    REQUIRE(l[1] == 2);
  }
}

template <typename T>
auto Lab1::List<T>::get(std::size_t index) -> T& {
  // TODO(colinaaa): check overflow
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::locate(const T e, std::function<bool(const T&, const T&)>&& eq) -> std::size_t {
  for (std::size_t i = 0; i < _length; i++) {
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
  REQUIRE(l.size() == 10);

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

template <typename T>
auto Lab1::List<T>::traverse(std::function<void(T&)>&& f) {
  for (auto&& i : *this) {
    f(i);
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
template <typename T>
auto Lab1::List<T>::resize(std::size_t size) {
  if (size < _size) {
    // TODO(error): throw error
    return;
  }

  auto p = std::make_unique<T[]>(size);
  auto oldElem = _elem.get();
  auto elem = p.get();
  for (std::size_t i = 0; i < _length; i++) {
    elem[i] = oldElem[i];
  }
  _elem.swap(p);
  _size = size;
}
template <typename T>
auto Lab1::List<T>::insert(std::size_t pos, const T& e) {
  if (pos > _size + 1 || pos < 1) {
    // TODO(error): throw error
    return;
  }

  if (_length == _size) {
    resize(_size * 2);
  }
  auto data = _elem.get();
  for (std::size_t i = _length; i >= pos; i--) {
    data[i] = data[i - 1];
  }
  _length++;
  data[pos - 1] = e;
}
template <typename T>
auto Lab1::List<T>::remove(std::size_t index) -> T {
  if (index < 1 || _length < index) {
    // TODO(error): throw error
  }
  auto out = _elem[index - 1];

  auto data = _elem.get();
  for (std::size_t i = index - 1; i < _length; i++) {
    data[i] = data[i + 1];
  }
  _length--;
  return out;
}

template <typename T>
auto Lab1::List<T>::remove(std::size_t index, T& out) {
  if (index < 1 || _length < index) {
    // TODO(error): throw error
  }
  out = _elem[index - 1];

  auto data = _elem.get();
  for (std::size_t i = index - 1; i < _length; i++) {
    data[i] = data[i + 1];
  }
  _length--;
}

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