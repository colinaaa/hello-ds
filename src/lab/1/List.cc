#include "List.hh"
#include <stdexcept>

template <typename T>
Lab1::List<T>::List() : _length(0), _size(1), _elem(std::make_unique<T[]>(1)) {}

template <typename T>
Lab1::List<T>::List(std::size_t size)
    : _length(0), _size(size), _elem(std::make_unique<T[]>(size)) {
  // see:
  // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
  if(size==0){
      throw std::underflow_error("init with index 0");
  }
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
