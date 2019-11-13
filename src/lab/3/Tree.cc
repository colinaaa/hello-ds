//
// Created by 王清雨 on 2019/11/12.
//

#include "Tree.hh"

template <typename T>
auto Lab3::Tree<T>::preOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("preOrder: root == nullptr");
  }
  return root()->preOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::inOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("inOrder: root == nullptr");
  }
  return root()->inOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::postOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("inOrder: root == nullptr");
  }
  return root()->postOrder(f);
}