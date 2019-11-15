//
// Created by 王清雨 on 2019/11/12.
//

#include "Tree.hh"

#include <stdexcept>

template <typename T>
auto Lab3::Tree<T>::preOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("preOrder: root == nullptr");
  }
  root()->preOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::inOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("inOrder: root == nullptr");
  }
  root()->inOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::postOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("inOrder: root == nullptr");
  }
  root()->postOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::levelOrderTraverse(std::function<void(T)> f) -> void {
  levelOrderTraverse([&](Node<T>* node) { f(node->data()); });
}

template <typename T>
auto Lab3::Tree<T>::levelOrderTraverse(std::function<void(Node<T>*)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("root == nullptr: level traverse");
  }
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

template <typename T>
Lab3::Tree<T>::Tree(const std::array<std::vector<T>, 2>& def) : _length(0), _root(nullptr) {
  const auto& [post, in] = def;
  if (post.size() != in.size()) {
    throw std::runtime_error("two definition size not equal");
  }
  _length = post.size();
  // setup cache
  auto cache = std::unordered_map<T, std::pair<int, int>>(_length);
  for (int i = 0; i < _length; ++i) {
    cache.insert({post[i], {i, -1}});
  }
  try {
    for (int j = 0; j < _length; ++j) {
      auto& item = cache.at(in[j]);
      item.second = j;
    }
  } catch (std::out_of_range& e) {
    throw std::runtime_error("two definition has different key");
  }
  auto postOrderIndex = [&cache](T x) { return cache.at(x).first; };
  auto inOrderIndex = [&cache](T x) { return cache.at(x).second; };

  auto rootIt = post.crbegin();
  auto rootIndex = inOrderIndex(*rootIt);
  auto lChildIndex = inOrderIndex(*(rootIt++));
  if (lChildIndex > rootIndex) {
    // has right child
    root()->right()->makeSubTree();
  } else {
    // no right child
    root()->left()->makeSubTree();
  }

  _root = std::make_unique<Node<T>>(*rootIt, _length - 1);
  auto lBegin = in.cbegin();
  auto lEnd = lBegin + (rootIndex - 1);
  auto rBegin = lBegin + (rootIndex + 1);
  auto rEnd = in.crend();
}
