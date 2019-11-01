#include "List.hh"

#include <memory>
#include <stdexcept>
#include <string>

template <typename T>
Lab2::List<T>::List() : _length(0), _first(nullptr) {}

template <typename T>
Lab2::List<T>::List(std::initializer_list<T> il) : _length(il.size()), _first(nullptr) {
  for (auto&& i : il) {
  }
}

template <typename T>
auto Lab2::List<T>::insert(const T& elem) -> void {
  if (_first == nullptr) {
    _first = std::make_unique<Node<T>>(Node(elem));
    _last = _first.get();
  } else {
    _last->_next = std::make_unique<Node<T>>(Node(elem));
    _last = _last->next();
  }
  _length++;
}

template <typename T>
auto Lab2::List<T>::get(std::size_t index) -> T& {
  if (index > _length) {
    throw std::overflow_error("get overflow, index: " + std::to_string(index));
  }
  Node<T>* pn = _first.get();
  for (std::size_t i = index; index != 0; index--) {
    pn = pn->next();
  }
  return pn->data();
}
