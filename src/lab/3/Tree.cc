//
// Created by 王清雨 on 2019/11/12.
//

#include "Tree.hh"

template <typename T>
Lab3::Tree<T>::Tree(std::initializer_list<T> iList)
    : _length(iList.size()), _root(std::make_unique<Node<T>>()) {
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
}
