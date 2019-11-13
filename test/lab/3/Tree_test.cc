//
// Created by 王清雨 on 2019/11/13.
//

#include "Tree.hh"
#include <catch2/catch.hpp>
TEST_CASE("tree") {
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
}