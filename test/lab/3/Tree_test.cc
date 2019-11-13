//
// Created by 王清雨 on 2019/11/13.
//

#include "Tree.hh"
#include <catch2/catch.hpp>
TEST_CASE("tree") {
  Lab3::Tree<int> t{
      1, 2, 3, 4, 10, 5, 6, 7,
  };
  SECTION("init list") {
    Lab3::Tree<int> tree{1, 2, 23, 4};
    REQUIRE(tree.length() == 4);
    REQUIRE(tree.root()->data() == 1);
    REQUIRE(tree.root()->left()->data() == 2);
    REQUIRE(tree.root()->right()->data() == 23);
    REQUIRE(tree.root()->right()->left() == nullptr);
    REQUIRE(tree.root()->left()->left()->data() == 4);
    REQUIRE(tree.root()->left()->right() == nullptr);
  }

  SECTION("pre order") {
    std::vector<int> res;
    t.preOrderTraverse([&res](int a) { res.push_back(a); });
    REQUIRE(res == std::vector{1, 2, 4, 7, 10, 3, 5, 6});
  }

  SECTION("in order") {
    std::vector<int> res;
    t.inOrderTraverse([&res](int x) { res.push_back(x); });
    REQUIRE(res == std::vector{7, 4, 2, 10, 1, 5, 3, 6});
  }

  SECTION("post order") {
    std::vector<int> res;
    t.postOrderTraverse([&res](int x) { res.push_back(x); });
    REQUIRE(res == std::vector{7, 4, 10, 2, 5, 6, 3, 1});
  }
}