//
// Created by 王清雨 on 2019/11/12.
//

#include "Node.hh"

template <typename T>
auto Lab3::Node<T>::insertLeft(T data) -> void {
  if (_left != nullptr) {
    throw std::runtime_error("already has left child");
  }
  auto ptr = std::make_unique<Node<T>>(data);

  _left = std::move(ptr);
}

template <typename T>
auto Lab3::Node<T>::insertLeft() -> void {
  return insertLeft(T{});
}

template <typename T>
auto Lab3::Node<T>::insertRight(T data) -> void {
  if (_right != nullptr) {
    throw std::runtime_error("already has left child");
  }
  auto ptr = std::make_unique<Node<T>>(data);

  _right = std::move(ptr);
}
template <typename T>
auto Lab3::Node<T>::insertRight() -> void {
  return insertRight(T{});
}
