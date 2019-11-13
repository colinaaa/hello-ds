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

template <typename T>
auto Lab3::Tree<T>::levelOrderTraverse(std::function<void(T)> f) -> void {
  levelOrderTraverse([&](Node<T>* node) { f(node->data()); });
}

template <typename T>
auto Lab3::Tree<T>::levelOrderTraverse(std::function<void(Node<T>*)> f) -> void {
  std::queue<Node<T>*> q;
  q.push(root());
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    f(node);
    if (node->left() != nullptr) {
      q.push(node->left());
    }
    if (node->right() != nullptr) {
      q.push(node->right());
    }
  }
}

template <typename T>
auto Lab3::Tree<T>::locate(int num) -> Lab3::Node<T>* {
  if (num > _length) {
    throw std::overflow_error("overflow: locate, index: " + std::to_string(num));
  }
  Node<T>* out = nullptr;
  levelOrderTraverse([&num, &out](Node<T>* node) -> void {
    if (node->_key == num) {
      out = node;
    }
  });
  return out;
}

template <typename T>
auto Lab3::Tree<T>::operator[](std::size_t i) -> Node<T>* {
  return locate(i);
}

template <typename T>
auto Lab3::Tree<T>::insert(T data, int key, InsertPlace lr) -> Node<T>* {
  auto node = locate(key);
  if (node == nullptr) {
    throw std::runtime_error("insert on non-exist node, key: " + std::to_string(key));
  }
  _length++;
  if (lr == InsertPlace::Left) {
    node->insertLeft(data);
    return node->left();
  } else {
    node->insertRight(data);
    return node->right();
  }
}

template <typename T>
auto Lab3::Tree<T>::depth() -> std::size_t {
  if (root() == nullptr) {
    return 0;
  }
  return root()->depth();
}
template <typename T>
auto Lab3::Tree<T>::remove(const int key) -> void {
  _length--;
  levelOrderTraverse([key](Node<T>* node) -> void {
    auto l = node->left();
    if (l != nullptr && l->key() == key) {
      // as for the constness and reference of newChild
      // see:
      // https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
      l->remove([&node](std::unique_ptr<Node<T>> newChild) -> void {
        // deleting the child and giving the ownership
        node->_left.swap(newChild);
      });
      return;
    }
    auto r = node->right();
    if (r != nullptr && r->key() == key) {
      r->remove([&node](std::unique_ptr<Node<T>> newChild) -> void {
        // deleting the child and giving the ownership
        node->_right.swap(newChild);
      });
      return;
    }
  });
}
