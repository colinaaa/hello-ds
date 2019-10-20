#include "List.hh"

template <typename T>
auto Lab1::List<T>::operator[](std::size_t index) noexcept(false) -> T& {
  if (index >= _size) {
    throw std::overflow_error("operator[] index: " + std::to_string(index));
  }
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::empty() -> bool {
  return _length == 0;
}

template <typename T>
auto Lab1::List<T>::get(std::size_t index) -> T& {
  if (index >= _size) {
    throw std::overflow_error("get index: " + std::to_string(index));
  }
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::locate(const T e, std::function<bool(const T&, const T&)>&& eq) -> std::size_t {
  for (std::size_t i = 0; i < _length; i++) {
    if (eq(e, _elem[i])) {
      return i;
    }
  }
  return -1;
}

template <typename T>
auto Lab1::List<T>::prior(const T& e) -> T& {
  auto pos = locate(e, [](const T& a, const T& b) { return a == b; });
  if (pos == 0) {
    throw std::underflow_error("prior");
  }
  if (pos > _length) {
    throw std::runtime_error("prior not found");
  }
  return _elem[pos - 1];
}

template <typename T>
auto Lab1::List<T>::next(const T& e) -> T& {
  auto pos = locate(e, [](const T& a, const T& b) { return a == b; });
  if (pos == _length - 1) {
    throw std::overflow_error("next");
  }
  if (pos > _length) {
    throw std::runtime_error("next not found");
  }
  return _elem[pos + 1];
}
