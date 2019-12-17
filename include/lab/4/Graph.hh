//
// Created by 王清雨 on 2019/12/9.
//
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

#ifndef HELLO_DS_GRAPH_HH
#define HELLO_DS_GRAPH_HH

namespace Lab4 {
template <typename T>
class Graph;
class Arc {
 public:
  Arc() = delete;
  Arc(std::size_t to, int weight) : _to(to), _weight(weight){};
  auto to() { return _to; };
  auto to() const { return _to; };

 private:
  std::size_t _to;  // _to is the index of the vertex that the arc linked to
  int _weight;
};

template <typename T>
class Node {
  friend class Graph<T>;

 public:
  explicit Node(T data) : _data(data){};
  Node(std::initializer_list<T>);

  auto addArc(std::size_t, int) -> void;
  auto aNum() { return _arc.size(); };
  auto data() -> T& { return _data; };
  auto data() const -> const T& { return _data; };

  auto dfs(std::function<void(Node<T>&)>) -> void;

 private:
  T _data;
  std::vector<Arc> _arc;
};

template <typename T>
class Graph {
 public:
  Graph() = default;
  Graph(std::initializer_list<Node<T>>);
  Graph(std::initializer_list<T>);

  auto vNum() { return _list.size(); };
  auto at(std::size_t i) const -> const Node<T>& { return _list[i]; };
  auto at(std::size_t i) -> Node<T>& { return _list[i]; };

  auto addNode(T) -> void;
  auto addNode(Node<T>) -> void;
  auto addArc(std::size_t, std::size_t, int = 1) -> void;

  auto locate(T) -> std::size_t;
  auto locate(T) const -> std::size_t;

  auto put(T, T) -> void;

  auto firstVex(std::size_t) -> T;
  auto nextVex(std::size_t, std::size_t) -> T;

  auto remove(std::size_t) -> void;
  auto remove(T) -> void;

  auto removeArc(T, T) -> void;

  auto bfs(std::function<void(Node<T>&)>) -> void;
  auto dfs(std::function<void(Node<T>&)>) -> void;

 private:
  std::vector<Node<T>> _list;
};

}  // namespace Lab4
#endif  // HELLO_DS_GRAPH_HH
