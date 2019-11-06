#include "Node.hh"

#include <memory>

// default init
template <typename T>
Lab2::Node<T>::Node() : _next(nullptr), _data() {}

// init with data
template <typename T>
Lab2::Node<T>::Node(T data) : _next(nullptr), _data(data) {}

template <typename T>
Lab2::Node<T>::Node(T data, std::unique_ptr<Node<T>>&& next)
    : _next(std::move(next)), _data(data) {}

// get next raw ptr
template <typename T>
auto Lab2::Node<T>::next() -> Node<T>* {
  return _next.get();
}

// get data
template <typename T>
auto Lab2::Node<T>::data() -> T& {
  return _data;
}
