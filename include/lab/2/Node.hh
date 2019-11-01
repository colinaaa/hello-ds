#ifndef NODE_HH
#define NODE_HH

#include <memory>

namespace Lab2 {
template <typename T>
class List;
template <typename T>
class Node {
 private:
  T _data;
  std::unique_ptr<Node<T>> _next;

  friend List<T>;

 public:
  Node();
  explicit Node(T);
  auto next() -> Node<T>*;
  auto data() -> T&;
};
}  // namespace Lab2

#endif  // NODE_HH
