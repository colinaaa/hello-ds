//
// Created by 王清雨 on 2019/11/12.
//
#include <queue>
#include "Node.hh"

#ifndef HELLO_DS_TREE_HH
#define HELLO_DS_TREE_HH
namespace Lab3 {
template <typename T>
class Tree {
 private:
  std::size_t _length;
  std::unique_ptr<Node<T>> _root;

 public:
  Tree() : _length(0), _root(nullptr){};
  Tree(std::initializer_list<T>);
  inline auto root() { return _root.get(); }
  inline auto length() { return _length; }
};
}  // namespace Lab3
#endif  // HELLO_DS_TREE_HH
