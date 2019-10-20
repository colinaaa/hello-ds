#ifndef SEQLIST_H
#define SEQLIST_H

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>

namespace Lab1 {
template <typename T>
class List {
  using File = std::string;

 private:
  std::size_t _length;  // len
  std::size_t _size;    // cap
  std::unique_ptr<T[]> _elem;

 public:
  List();
  explicit List(std::size_t);      // init with size
  List(std::initializer_list<T>);  // init with initializer_list

  // range-based loop
  [[nodiscard]] auto begin() const -> T * { return _length > 0 ? &_elem[0] : nullptr; }
  //! There is an array overflow that I used for the range-base for loop
  //! should implement Iterator class instead of this
  [[nodiscard]] auto end() const -> T * { return _length > 0 ? &_elem[_length] : nullptr; }

  // cap/len stuff
  [[nodiscard]] inline auto size() const { return _size; }
  [[nodiscard]] inline auto length() const { return _length; }
  auto empty() -> bool;

  // elements operations
  auto operator[](std::size_t) noexcept(false) -> T &;
  auto get(std::size_t) -> T &;
  auto locate(T, std::function<bool(const T &, const T &)> &&) -> std::size_t;
  auto prior(const T &) -> T &;
  auto next(const T &) -> T &;

  auto traverse(std::function<void(T &)> &&) -> void;

  auto resize(std::size_t) -> void;
  auto insert(std::size_t, const T &) -> void;
  auto remove(std::size_t, T &) -> void;
  auto remove(std::size_t) -> T;

  auto save(File &&f);

  auto load(File &&f);
};
}  // namespace Lab1

#endif  // SEQLIST_H
