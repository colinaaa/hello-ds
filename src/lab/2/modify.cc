#include "List.hh"

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
auto Lab2::List<T>::insert(std::size_t index, const T& elem) -> void {
  _length++;
  auto p = _first.get();
  while (index != 1) {
    p = p->next();
    index--;
  }
  auto ptr = std::make_unique<Node<T>>(elem, std::move(p->_next));
  p->_next = std::move(ptr);
}

template <typename T>
auto Lab2::List<T>::remove(std::size_t index) -> T {
  if (index == 0) {
    throw std::underflow_error("remove underflow index: " + std::to_string(index));
  }
  if (index > _length) {
    throw std::overflow_error("remove overflow index: " + std::to_string(index));
  }
  T out;
  if (index == 1) {
    out = _first.get()->data();
    _first = std::move(_first.get()->_next);
  } else {
    auto p = _first.get();
    while (index != 2) {
      p = p->next();
      index--;
    }
    out = p->_next.get()->data();
    p->_next = std::move(p->_next.get()->_next);
  }
  _length--;
  return out;
}

template <typename T>
auto Lab2::List<T>::clear() noexcept -> void {
  _first = nullptr;
  _length=0;
}
