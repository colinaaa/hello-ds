//
// Created by 王清雨 on 2019/12/9.
//

#include "Graph.hh"

#include <catch2/catch.hpp>
#include <stdexcept>

TEST_CASE("Graph") {
  Lab4::Graph<int> g{1, 2};
  REQUIRE(g.vNum() == 2);
  g.addArc(0, 1);
  REQUIRE(g.at(0).aNum() == 1);

  SECTION("add") {
    g.addNode(3);
    g.addNode(4);
    REQUIRE(g.vNum() == 4);
  }

  SECTION("at") {
    const Lab4::Graph<int> cg{1, 2, 3, 4, 5, 6};
    REQUIRE(cg.at(4).data() == 5);
  }

  SECTION("locate") {
    REQUIRE(g.locate(2) == 1);
    REQUIRE_THROWS_AS(g.locate(100), std::runtime_error);
  }

  SECTION("put") {
    g.put(1, 100);
    REQUIRE(g.at(0).data() == 100);
  }

  SECTION("vex") {
    REQUIRE(g.firstVex(0) == 2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addArc(0, 2);
    g.addArc(0, 3);
    REQUIRE(g.at(0).aNum() == 3);
    REQUIRE(g.nextVex(0, 2) == 4);
    REQUIRE_THROWS_AS(g.nextVex(1, 100), std::range_error);
    REQUIRE_THROWS_AS(g.nextVex(100, 100), std::overflow_error);
    g.removeArc(1, 2);
    REQUIRE(g.at(0).aNum() == 2);
    REQUIRE(g.at(g.nextVex(0, 0)).data() == 4);
  }

  SECTION("remove") {
    g.addNode(3);
    g.addNode(4);
    g.addArc(1, 0);
    REQUIRE(g.firstVex(0) == 2);
    REQUIRE(g.firstVex(1) == 1);
    g.removeArc(1, 2);
    REQUIRE_THROWS_AS(g.firstVex(0), std::runtime_error);
  }

  SECTION("search") {
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addArc(0, 3);
    g.addArc(3, 2);
    g.addArc(2, 4);
    std::vector<int> res;
    g.bfs([&res](Lab4::Node<int>& n) { res.push_back(n.data()); });
    REQUIRE(res == std::vector{1, 2, 4, 3, 5});
    std::vector<int> res2;
    g.dfs([&res2](Lab4::Node<int>& n) { res2.push_back(n.data()); });
    REQUIRE(res2 == std::vector{1, 4, 3, 5, 2});
  }
}

TEST_CASE("Node4") {
  Lab4::Node<int> n(1);
  Lab4::Node<int> n2{2};
}
