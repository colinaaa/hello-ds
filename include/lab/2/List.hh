#ifndef LIST_HH
#define LIST_HH

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>

#include "Node.hh"

namespace Lab2 {
template <typename T>
class List {
  using File = std::string;

 private:
  std::size_t _length;  // len
  std::unique_ptr<Node<T>> _first;
  Node<T> *_last = nullptr;

 public:
  List();
  List(std::initializer_list<T>);  // init with initializer_list

  auto operator==(const List<T> &rhs) const -> bool;
  [[nodiscard]] inline auto length() const { return _length; }
  inline auto empty() const { return _length == 0; }

  // elements operations
  auto get(std::size_t) -> T &;
  auto get(std::size_t) const -> const T &;
  auto locate(T, std::function<bool(const T &, const T &)> &&) -> std::size_t;
  auto prior(const T &) -> T &;
  auto next(const T &) -> T &;

  auto traverse(std::function<void(T &)> &&) -> void;

  auto insert(std::size_t, const T &) -> void;
  auto insert(const T &) -> void;
  auto remove(std::size_t) -> T;

  auto clear() noexcept -> void;
};
}  // namespace Lab2

#endif  // LIST_HH
