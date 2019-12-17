//
// Created by 王清雨 on 2019/11/12.
//

#include "Tree.hh"

#include <stack>

template <typename T>
auto Lab3::Tree<T>::preOrderTraverse(std::function<void(T)> f) -> void {
  if (root() == nullptr) {
    throw std::runtime_error("preOrder: root == nullptr");
  }
  root()->preOrder(f);
}

template <typename T>
auto Lab3::Tree<T>::preOrderTraverse(std::function<void(T)> f, bool /*unused*/) -> void {
  std::stack<Node<T>*> s;
  s.push(root());
  while (!s.empty()) {
    auto n = s.top();
    s.pop();
    f(n->data());
    if (n->right() != nullptr) {
      s.push(n->right());
    }
    if (n->left() != nullptr) {
      s.push(n->left());
    }
  }
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
  }
  node->insertRight(data);
  return node->right();
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
Lab3::Tree<T>::Tree(const std::array<std::vector<T>, 2>& def) : _root(nullptr) {
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

  for (int j = 0; j < _length; ++j) {
    auto& item = cache.at(in[j]);
    item.second = j;
  }
  auto index = [&cache](T x, bool first) { return first ? cache.at(x).first : cache.at(x).second; };
  auto rootNode = makeSubTree(in, post, index, 0, _length - 1, 0, _length - 1);
  _root.swap(rootNode);
}

// full of shits that I even could not understand
template <typename T>
auto Lab3::Tree<T>::makeSubTree(const std::vector<T>& in, const std::vector<T>& post,
                                std::function<int(T, bool)> index, int inBegin, int inEnd,
                                int postBegin, int postEnd) -> std::unique_ptr<Node<T>> {
  if (inBegin == inEnd) {
    return std::make_unique<Node<T>>(in[inBegin], inBegin);
  }
  // first(true) -> post , second(false) -> in;
  auto root = post[postEnd];
  std::unique_ptr<Node<T>> left = nullptr;
  std::unique_ptr<Node<T>> right = nullptr;
  auto rootIndex = index(root, false);  // in
  if (rootIndex != inEnd) {
    // has right child
    auto rInBegin = rootIndex + 1;
    auto length = inEnd - rInBegin + 1;
    auto rightChild = makeSubTree(in, post, index, rInBegin, inEnd, postEnd - length, postEnd - 1);
    auto rootNode = std::make_unique<Node<T>>(root, rootIndex);
    rootNode.get()->_right = std::move(rightChild);
    if (rootIndex == inBegin) {
      // no left child
      return std::move(rootNode);
    }
    auto leftChild =
        makeSubTree(in, post, index, inBegin, rootIndex - 1, postBegin, postEnd - 1 - length);
    rootNode.get()->_left = std::move(leftChild);
    return std::move(rootNode);
  }
  // no right child
  auto child = makeSubTree(in, post, index, inBegin, rootIndex - 1, postBegin, postEnd - 1);
  auto rootNode = std::make_unique<Node<T>>(root, rootIndex);
  rootNode.get()->_left = std::move(child);
  return std::move(rootNode);
}

template <typename T>
auto Lab3::Tree<T>::preAndIn(const std::vector<T>& in, const std::vector<T>& pre,
                             std::function<int(T, bool)> index, int inBegin, int inEnd,
                             int preBegin, int preEnd) -> std::unique_ptr<Node<T>> {
  if (inBegin == inEnd) {
    return std::make_unique<Node<T>>(in[inBegin], inBegin);
  }
  // first(true) -> pre , second(false) -> in;
  auto root = pre[preEnd];
  std::unique_ptr<Node<T>> left = nullptr;
  std::unique_ptr<Node<T>> right = nullptr;
  auto rootIndex = index(root, false);  // in
  if (rootIndex != inEnd) {
    // has right child
    auto rInBegin = rootIndex + 1;
    auto length = inEnd - rInBegin + 1;
    auto rightChild = makeSubTree(in, pre, index, rInBegin, inEnd, preEnd - length, preEnd - 1);
    auto rootNode = std::make_unique<Node<T>>(root, rootIndex);
    rootNode.get()->_right = std::move(rightChild);
    if (rootIndex == inBegin) {
      // no left child
      return std::move(rootNode);
    }
    auto leftChild =
        makeSubTree(in, pre, index, inBegin, rootIndex - 1, preBegin, preEnd - 1 - length);
    rootNode.get()->_left = std::move(leftChild);
    return std::move(rootNode);
  }
  // no right child
  auto child = makeSubTree(in, pre, index, inBegin, rootIndex - 1, preBegin, preEnd - 1);
  auto rootNode = std::make_unique<Node<T>>(root, rootIndex);
  rootNode.get()->_left = std::move(child);
  return std::move(rootNode);
}
