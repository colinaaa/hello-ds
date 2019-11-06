#include "List.hh"

template <typename T>
auto Lab2::List<T>::get(std::size_t index) -> T& {
  if (index == 0) {
    throw std::underflow_error("get underflow, index: " + std::to_string(index));
  }
  if (index > _length) {
    throw std::overflow_error("get overflow, index: " + std::to_string(index));
  }
  auto pn = _first.get();
  for (std::size_t i = index; index != 1; index--) {
    pn = pn->next();
  }
  return pn->data();
}

template <typename T>
auto Lab2::List<T>::get(std::size_t index) const -> T {
  if (index == 0) {
    throw std::underflow_error("get underflow, index: " + std::to_string(index));
  }
  if (index > _length) {
    throw std::overflow_error("get overflow, index: " + std::to_string(index));
  }
  auto pn = _first.get();
  for (std::size_t i = index; index != 1; index--) {
    pn = pn->next();
  }
  return pn->data();
}
// locate return 1~length, and 0 for not found
template <typename T>
auto Lab2::List<T>::locate(T elem, std::function<bool(const T&, const T&)>&& eq) -> std::size_t {
  auto p1 = _first.get();
  auto p2 = _first.get();
  std::size_t index = 0;
  while (p1 != nullptr) {
    index++;
    if (eq(p1->_data, elem)) {
      return index;
    }
    p2 = p1;
    p1 = p1->next();
  }
  return 0;
}

template <typename T>
auto Lab2::List<T>::prior(const T& elem) -> T& {
  auto p1 = _first.get()->next();
  auto p2 = _first.get();
  while (p1 != nullptr) {
    if (p1->_data == elem) {
      return p2->_data;
    }
    p2 = p1;
    p1 = p1->next();
  }
  throw std::runtime_error("prior: not found");
}

template <typename T>
auto Lab2::List<T>::next(const T& elem) -> T& {
  auto p1 = _first.get()->next();
  auto p2 = _first.get();
  while (p1 != nullptr) {
    if (p2->_data == elem) {
      return p1->_data;
    }
    p2 = p1;
    p1 = p1->next();
  }
  throw std::runtime_error("next: not found");
}

