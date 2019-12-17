//
// Created by 王清雨 on 2019/11/12.
//
#include <array>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include "Node.hh"

#ifndef HELLO_DS_TREE_HH
#define HELLO_DS_TREE_HH
namespace Lab3 {
template <typename T>
class Tree {
 private:
  enum class InsertPlace { Left, Right };

 public:
  static inline auto Left() { return InsertPlace::Left; }
  static inline auto Right() { return InsertPlace::Right; }

 private:
  std::size_t _length{};
  std::unique_ptr<Node<T>> _root{nullptr};

 public:
  inline auto root() { return _root.get(); }
  inline auto length() { return _length; }
  inline auto empty() { return _length == 0; }
  inline auto clear() {
    // may got stack overflow here, see:
    // https://stackoverflow.com/questions/35535312/stack-overflow-with-unique-ptr-linked-list
    _root.reset();
    _length = 0;
  }
  auto depth() -> std::size_t;

 public:
  Tree() : _root(nullptr){};
  Tree(std::initializer_list<T> iList) : _length(iList.size()), _root(std::make_unique<Node<T>>()) {
    if (_length == 0) {
      return;
    }
    std::queue<Node<T>*> q;
    q.push(root());
    std::size_t index = 0;
    auto n = iList.size();
    for (auto&& i : iList) {
      index++;
      auto ptr = q.front();
      q.pop();
      ptr->_data = i;
      ptr->_key = index;
      if (index * 2 < n) {
        ptr->insertLeft();
        q.push(ptr->left());
        ptr->insertRight();
        q.push(ptr->right());
      } else if (index * 2 == n) {
        ptr->insertLeft();
        q.push(ptr->left());
      }
    }
  };

 private:
  const char Blank = '@';

 public:
  explicit Tree(const std::array<std::vector<T>, 2>&);

 public:
  auto preOrderTraverse(std::function<void(T)>) -> void;
  auto preOrderTraverse(std::function<void(T)>, bool) -> void;
  auto inOrderTraverse(std::function<void(T)>) -> void;
  auto postOrderTraverse(std::function<void(T)>) -> void;
  auto levelOrderTraverse(std::function<void(T)>) -> void;
  auto levelOrderTraverse(std::function<void(Node<T>*)>) -> void;

 public:
  auto locate(int) -> Node<T>*;
  auto operator[](std::size_t) -> Node<T>*;
  auto insert(T, int, InsertPlace) -> Node<T>*;
  auto remove(int) -> void;
  auto makeSubTree(const std::vector<T>&, const std::vector<T>&, std::function<int(T, bool)>, int,
                   int, int, int) -> std::unique_ptr<Node<T>>;
  auto preAndIn(const std::vector<T>&, const std::vector<T>&, std::function<int(T, bool)>, int, int,
                int, int) -> std::unique_ptr<Node<T>>;
};

}  // namespace Lab3
#endif  // HELLO_DS_TREE_HH
