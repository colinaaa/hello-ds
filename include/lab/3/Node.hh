//
// Created by 王清雨 on 2019/11/12.
//
#include <memory>
#ifndef HELLO_DS_NODE_HH
#define HELLO_DS_NODE_HH

template <typename T>
class Node {
 private:
  std::unique_ptr<Node<T>> _left;
  std::unique_ptr<Node<T>> _right;

  T _data;

 public:
  Node() : _left(nullptr), _right(nullptr), _data(){};
  explicit Node(T data) : _left(nullptr), _right(nullptr), _data(data){};
  inline auto left() -> T* { return _left.get(); }
  inline auto right() -> T* { return _right.get(); }
  inline auto data() const -> T { return data; }
  inline auto data() -> T& { return data; }
};

#endif  // HELLO_DS_NODE_HH
