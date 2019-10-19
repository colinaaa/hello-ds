#ifndef SEQLIST_H
#define SEQLIST_H

#include <initializer_list>
#include <memory>
#include <string>

namespace Lab1 {
template <typename T>
class List {
  using File = std::string;

 private:
  int _length;  // len
  int _size;    // cap
  std::unique_ptr<T[]> _elem;

 public:
  List();
  explicit List(int);              // init with size
  List(std::initializer_list<T>);  // init with initializer_list

  // range-based loop
  [[nodiscard]] auto begin() const -> int * { return _length > 0 ? &_elem[0] : nullptr; }
  //! There is an array overflow that I used for the range-base for loop
  //! should implement Iterator class instead of this
  [[nodiscard]] auto end() const -> int * { return _length > 0 ? &_elem[_length] : nullptr; }

  // cap/len stuff
  [[nodiscard]] inline auto size() const { return _size; }
  [[nodiscard]] inline auto length() const { return _length; }
  auto empty() -> bool;

  // elements operations
  auto operator[](uint) -> T &;
  auto get(int) -> T &;
  auto locate(T, std::function<bool(const T &, const T &)> &&) -> int;
  auto prior(const T &) -> T &;
  auto next(const T &) -> T &;

  auto traverse(std::function<void(T &)> &&);

  auto save(File &&f);

  auto load(File &&f);
};
}  // namespace Lab1

#endif  // SEQLIST_H
