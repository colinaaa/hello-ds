#include "Graph.hh"

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>


template <typename T>
Lab4::Graph<T>::Graph(std::initializer_list<T> iList) : _list(std::vector<Node<T>>()) {
  for (auto&& i : iList) {
    _list.emplace_back(i);
  }
}
template <typename T>
auto Lab4::Graph<T>::addNode(T data) -> void {
  _list.emplace_back(data);
}

template <typename T>
auto Lab4::Graph<T>::addArc(std::size_t from, std::size_t to, int weight) -> void {
  if (from >= _list.size()) {
    throw std::overflow_error("add arc has from: " + std::to_string(from) +
                              " but has size: " + std::to_string(_list.size()));
  }
  _list[from].addArc(to, weight);
}

template <typename T>
auto Lab4::Graph<T>::locate(const T data) -> std::size_t {
  auto f = std::find_if(_list.cbegin(), _list.cend(),
                        [data](const Node<T>& n) { return n.data() == data; });

  if (f == _list.cend()) {
    throw std::runtime_error("locate not found with data" + std::to_string(data));
  }
  return f - _list.cbegin();
}

template <typename T>
auto Lab4::Graph<T>::put(const T src, const T dst) -> void {
  auto i = locate(src);
  at(i)._data = dst;
}

template <typename T>
auto Lab4::Graph<T>::firstVex(const std::size_t i) -> T {
  if (i >= _list.size()) {
    throw std::overflow_error("firstVex overflow with index: " + std::to_string(i));
  }
  auto arc = _list[i]._arc;
  if (arc.empty()) {
    throw std::range_error("first vex of " + std::to_string(i) + " not found");
  }

  auto to = arc.at(0).to();
  return at(to).data();
}

template <typename T>
auto Lab4::Graph<T>::nextVex(std::size_t i, std::size_t j) -> T {
  if (i >= _list.size()) {
    throw std::overflow_error("nextVex overflow with index: " + std::to_string(i));
  }
  auto arc = _list[i]._arc;
  if (arc.size() <= j) {
    throw std::range_error(std::to_string(j) + " th vex of " + std::to_string(i) + " not found");
  }
  return at(arc.at(j).to()).data();
}

template <typename T>
auto Lab4::Graph<T>::remove(std::size_t i) -> void {
  if (i >= _list.size()) {
    throw std::overflow_error("remove overflow with index: " + std::to_string(i));
  }
  for (auto&& node : _list) {
    auto it = std::find_if(node._arc.cbegin(), node._arc.cend(),
                           [i](const Arc a) { return a.to() == i; });
    if(it!=node._arc.cend()){
      node._arc.erase(it);
    }
  }
  _list.erase(_list.begin() + i);
}

template <typename T>
auto Lab4::Graph<T>::remove(const T data) -> void {
  auto i = locate(data);
  remove(i);
}

template <typename T>
auto Lab4::Graph<T>::removeArc(const T a, const T b) -> void {
  auto from = locate(a);
  auto _to = locate(b);
  auto& arc = _list.at(from)._arc;
  auto to = std::find_if(arc.cbegin(), arc.cend(), [b, _to](const Arc a) { return a.to() == _to; });
  arc.erase(to);
}

template <typename T>
auto Lab4::Graph<T>::bfs(std::function<void(Node<T>&)> visit) -> void {
  std::vector<int> cache(_list.size() + 1, 0);
  std::queue<Node<T>> q;

  for (int j = 0; j < _list.size(); j++) {
    if (cache.at(j) != 0) {
      continue;
    }
    q.push(_list.at(j));
    while (!q.empty()) {
      auto n = q.front();
      q.pop();
      cache.at(n.data()) = 0xff;
      visit(n);
      for (const auto& i : n._arc) {
        if (cache.at(at(i.to()).data()) == 0) {
          q.push(_list.at(i.to()));
        }
      }
    }
  }
}

template <typename T>
auto Lab4::Graph<T>::dfs(std::function<void(Node<T>&)> visit) -> void {
  if (_list.empty()) {
    throw std::range_error("dfs empty graph");
  }
  std::vector<int> cache(_list.size() + 1, 0);
  std::stack<std::size_t> s;
  for (int i = 0; i < _list.size(); i++) {
    if (cache.at(i) != 0) {
      continue;
    }
    s.push(i);
    while (!s.empty()) {
      auto index = s.top();
      s.pop();
      cache.at(index) = 0xff;
      visit(_list.at(index));
      for (auto& arc : _list.at(index)._arc) {
        if (cache.at(arc.to()) == 0) {
          s.push(arc.to());
        }
      }
    }
  }
}
