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
template <typename T>
auto Lab3::Node<T>::depth() -> std::size_t {
  if (left() == nullptr) {
    if (right() == nullptr) {
      return 1;
    } else {
      return right()->depth() + 1;
    }
  } else {
    if (right() == nullptr) {
      return left()->depth() + 1;
    } else {
      return std::max(left()->depth(), right()->depth()) + 1;
    }
  }
}
template <typename T>
auto Lab3::Node<T>::remove(std::function<void(std::unique_ptr<Node<T>>)> cleanUp) -> void {
  // cleanUp is a lambda to release the node's unique_ptr and set up correct new child
  if (left() == nullptr) {
    if (right() != nullptr) {
      // only has right child
      cleanUp(std::move(_right));
      return;
    }
    cleanUp(nullptr);
    return;
  }

  // left != nullptr
  if (right() == nullptr) {
    cleanUp(std::move(_left));
    return;
  }

  // left != nullptr && right != nullptr
  // using left as new root and move right to the rightest place of the left tree
  auto p = left();
  while (p->right() != nullptr) {
    p = p->right();
  }
  p->_right = std::move(_right);
  cleanUp(std::move(_left));
}