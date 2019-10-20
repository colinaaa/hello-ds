#include <iostream>

#include "1/List.hh"

// things about link error:
// see:
// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
// and
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl

auto main() -> int {
  Lab1::List<std::string> list{"1", "2", "3", "4"};
  for (auto &&i : list) {
    std::cout << i;
  }
  return 0;
}