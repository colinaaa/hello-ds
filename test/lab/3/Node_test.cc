//
// Created by 王清雨 on 2019/11/12.
//
#include "Node.hh"

#include <Tree.hh>
#include <catch2/catch.hpp>
TEST_CASE("Node3") {
  SECTION("init with default value") {
    Lab3::Node<int> node{};
    REQUIRE(node.left() == nullptr);
    REQUIRE(node.right() == nullptr);
    REQUIRE(node.data() == 0);
    const Lab3::Node<double> cNode{};
    REQUIRE(cNode.data() == 0);
  }
}
