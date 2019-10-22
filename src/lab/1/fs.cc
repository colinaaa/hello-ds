#include <fstream>

#include "List.hh"

template <typename T>
auto Lab1::List<T>::save(File &&f) -> void {
  std::ofstream fs;
  fs.open(f);
  for (auto &&i : *this) {
    fs << i << std::endl;
  }
  fs.close();
}

template <typename T>
auto Lab1::List<T>::load(File &&f) -> void {
  std::ifstream fs;
  fs.open(f);
  T buf;
  while (fs >> buf) {
    insert(buf);
  }

  fs.close();
}