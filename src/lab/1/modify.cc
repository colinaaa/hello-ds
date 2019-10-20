#include "List.hh"

template <typename T>
auto Lab1::List<T>::resize(std::size_t size) -> void {
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
auto Lab1::List<T>::insert(std::size_t pos, const T& e) -> void {
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
auto Lab1::List<T>::remove(std::size_t index, T& out) -> void {
  if (index < 1 || _length < index) {
    // TODO(error): throw error
    return;
  }
  out = _elem[index - 1];

  auto data = _elem.get();
  for (std::size_t i = index - 1; i < _length; i++) {
    data[i] = data[i + 1];
  }
  _length--;
}
