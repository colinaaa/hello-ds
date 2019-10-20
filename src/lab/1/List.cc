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
auto Lab1::List<T>::traverse(std::function<void(T&)>&& f) -> void {
  for (auto&& i : *this) {
    f(i);
  }
}
