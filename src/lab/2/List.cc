#include "List.hh"

template <typename T>
Lab2::List<T>::List() : _length(0), _first(nullptr) {}

template <typename T>
Lab2::List<T>::List(std::initializer_list<T> il) : _length(0), _first(nullptr) {
  for (auto&& i : il) {
    insert(i);
  }
}
template <typename T>
auto Lab2::List<T>::traverse(std::function<void(T&)>&& visit) -> void {
  auto p = _first.get();
  while (p != nullptr) {
    visit(p->data());
    p = p->next();
  }
}
template <typename T>
auto Lab2::List<T>::operator==(const List<T>& rhs) const -> bool {
  if (length() != rhs.length()) {
    return false;
  }
  for (std::size_t i; i < _length; i++) {
    if (get(i) != rhs.get(i)) {
      return false;
    }
  }
  return true;
}

