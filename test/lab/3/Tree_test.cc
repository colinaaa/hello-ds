//
// Created by 王清雨 on 2019/11/13.
//

#include "Tree.hh"
#include <catch2/catch.hpp>
TEST_CASE("tree") {
  Lab3::Tree<int> t{
      1, 2, 3, 4, 10, 5, 6, 7,
  };
  REQUIRE(t.length() == 8);
  REQUIRE(t.depth() == 4);
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

  SECTION("level order") {
    std::vector<int> res;
    t.levelOrderTraverse([&res](int x) { res.push_back(x); });
    REQUIRE(res == std::vector{1, 2, 3, 4, 10, 5, 6, 7});
    res.clear();
    t.levelOrderTraverse([&res](Lab3::Node<int>* n) { res.push_back(n->data()); });
    REQUIRE(res == std::vector{1, 2, 3, 4, 10, 5, 6, 7});
  }
}

TEST_CASE("Lab3/locate", "[Lab3, Tree]") {
  Lab3::Tree<int> t{1, 2, 3, 4, 5, 6, 7};
  REQUIRE(t.length() == 7);

  for (std::size_t i = 1; i < t.length() + 1; ++i) {
    REQUIRE(t.locate(i)->data() == i);
  }
}

TEST_CASE("Lab3/insert", "[Lab3, Tree]") {
  Lab3::Tree<int> t{1, 2, 3, 4, 5, 6, 7, 8};
  REQUIRE(t.length() == 8);

  SECTION("to right") {
    auto r = t.insert(999, 4, Lab3::Tree<int>::Right());
    REQUIRE(t.length() == 9);
    REQUIRE(r->data() == 999);
    REQUIRE(r->left() == nullptr);
    REQUIRE(r->right() == nullptr);
    REQUIRE(t.locate(4)->right() == r);
  }

  SECTION("to left") {
    auto r = t.insert(10000, 5, Lab3::Tree<int>::Left());
    REQUIRE(t.length() == 9);
    REQUIRE(r->data() == 10000);
    REQUIRE(r->left() == nullptr);
    REQUIRE(r->right() == nullptr);
    REQUIRE(t.locate(5)->left() == r);
  }
}

TEST_CASE("Lab3/remove", "[Lab3, Tree]") {
  Lab3::Tree<int> t{1, 2, 3, 4, 5, 6, 7, 8, 9};

  SECTION("from tail with no children") {
    t.remove(9);
    REQUIRE(t.length() == 8);
    REQUIRE(t.locate(4)->right() == nullptr);
    REQUIRE_THROWS_AS(t.locate(9), std::overflow_error);
  }

  SECTION("from middle with two children") {
    t.remove(2);
    REQUIRE(t.length() == 8);
    std::vector<int> res;
    t.levelOrderTraverse([&res](int x) { res.push_back(x); });
    REQUIRE(res == std::vector{1, 4, 3, 8, 9, 6, 7, 5});
  }
}