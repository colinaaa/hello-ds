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
  int _length;
  int _size;
  std::unique_ptr<T[]> _elem;

 public:
  List();
  // init with a length
  explicit List(int);
  List(std::initializer_list<T>);
  [[nodiscard]] inline auto size() const { return _size; }
  auto operator[](uint) -> T &;
  auto empty() -> bool;

  auto save(File &&f);

  auto load(File &&f);

  static auto destroy(List *L);

  auto clear();

  [[nodiscard]] inline auto length() const { return _length; }

  auto get(int) -> T &;

  auto locate(T, bool(const T &, const T &)) -> int;

  auto prior(const T &) -> T &;

  auto next(const T &) -> T &;

  auto insertBefore(int index, T elem) -> T &;

  auto remove(int index) -> T;

  void forEach(void (*callback)(T &elem));

  auto push(T) -> int;

  auto pop() -> T;
};
}  // namespace Lab1

#endif  // SEQLIST_H
