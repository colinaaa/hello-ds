//
// Created by 王清雨 on 2019/11/12.
//
#include <algorithm>
#include <functional>
#include <memory>
#ifndef HELLO_DS_NODE_HH
#define HELLO_DS_NODE_HH

namespace Lab3 {
template <typename T>
class Tree;

template <typename T>
class Node {
  friend Tree<T>;

 private:
  std::unique_ptr<Node<T>> _left;
  std::unique_ptr<Node<T>> _right;

  int _key;
  T _data;

 public:
  Node() : _left(nullptr), _right(nullptr), _data(), _key(){};
  explicit Node(T data) : _left(nullptr), _right(nullptr), _data(data), _key(){};
  Node(T data, int key) : _left(nullptr), _right(nullptr), _data(data), _key(key){};
  inline auto left() { return _left.get(); }
  inline auto right() { return _right.get(); }
  inline auto data() const -> T { return _data; }
  inline auto data() -> T& { return _data; }
  inline auto key() const { return _key; }

 public:
  auto insertLeft() -> void;
  auto insertRight() -> void;
  auto insertLeft(T) -> void;
  auto insertRight(T) -> void;

 public:
  auto preOrder(std::function<void(T)>) -> void;
  auto inOrder(std::function<void(T)>) -> void;
  auto postOrder(std::function<void(T)>) -> void;

 public:
  auto depth() -> std::size_t;

 public:
  auto remove(std::function<void(std::unique_ptr<Node<T>>)>) -> void;
};
}  // namespace Lab3

#endif  // HELLO_DS_NODE_HH
