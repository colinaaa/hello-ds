#include "List.hh"

template <typename T>
auto Lab1::List<T>::operator[](std::size_t index) -> T& {
  // TODO(colinaaa): throw error when overflow
  return _elem[index];
}

template <typename T>
auto Lab1::List<T>::empty() -> bool {
  return _length == 0;
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
  auto pos = locate(e, [](const T& a, const T& b) { return a == b; });
  // TODO(colinaaa): check whether pos == 0 or overflow
  if (pos < 0) {
    return _elem[pos];
  }
  return _elem[pos - 1];
}

template <typename T>
auto Lab1::List<T>::next(const T& e) -> T& {
  auto pos = locate(e, [](const T& a, const T& b) { return a == b; });
  // TODO(colinaaa): check whether pos == length or underflow
  if (pos == _length) {
    return _elem[pos];
  }
  return _elem[pos + 1];
}
