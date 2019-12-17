
#include "Graph.hh"

template <typename T>
Lab4::Node<T>::Node(std::initializer_list<T> iList) : _data() {
  if (iList.size() == 0) {
    throw std::underflow_error("node init list has size 0");
  }
  _data = *iList.begin();
}

template <typename T>
auto Lab4::Node<T>::addArc(std::size_t to, int weight) -> void {
  _arc.emplace_back(to, weight);
}

