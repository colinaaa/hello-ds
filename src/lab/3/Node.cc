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

template <typename T>
auto Lab3::Node<T>::preOrder(std::function<void(T)> f) -> void {
  f(data());
  if (left() != nullptr) {
    left()->preOrder(f);
  }
  if (right() != nullptr) {
    right()->preOrder(f);
  }
}
template <typename T>
auto Lab3::Node<T>::inOrder(std::function<void(T)> f) -> void {
  if (left() != nullptr) {
    left()->inOrder(f);
  }
  f(data());
  if (right() != nullptr) {
    right()->inOrder(f);
  }
}

template <typename T>
auto Lab3::Node<T>::postOrder(std::function<void(T)> f) -> void {
  if (left() != nullptr) {
    left()->postOrder(f);
  }
  if (right() != nullptr) {
    right()->postOrder(f);
  }
  f(data());
}