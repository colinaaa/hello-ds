#include "List.hh"

template <typename T>
auto Lab1::List<T>::resize(std::size_t size) -> void {
  if (size < _size) {
    throw std::length_error("resize with size" + std::to_string(size));
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
auto Lab1::List<T>::insert(std::size_t pos, const T& e) -> void {
  if (pos > _size + 1) {
    throw std::overflow_error("insert index: " + std::to_string(pos));
  }
  if (pos < 1) {
    throw std::underflow_error("insert index: " + std::to_string(pos));
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
  if (index < 1) {
    throw std::underflow_error("remove index: " + std::to_string(index));
  }
  if (_length < index) {
    throw std::overflow_error("remove index: " + std::to_string(index));
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
auto Lab1::List<T>::remove(std::size_t index, T& out) -> void {
  if (index < 1) {
    throw std::underflow_error("remove index: " + std::to_string(index));
  }
  if (_length < index) {
    throw std::overflow_error("remove index: " + std::to_string(index));
    return;
  }
  out = _elem[index - 1];

  auto data = _elem.get();
  for (std::size_t i = index - 1; i < _length; i++) {
    data[i] = data[i + 1];
  }
  _length--;
}
