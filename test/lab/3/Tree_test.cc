//
// Created by 王清雨 on 2019/11/13.
//

#include "Tree.hh"

#include <catch2/catch.hpp>
#include <stdexcept>
#include <vector>
TEST_CASE("Lab3/init", "[Lab3, Tree]") {
  Lab3::Tree<int> t{
      1, 2, 3, 4, 10, 5, 6, 7,
  };
  REQUIRE(t.length() == 8);
  REQUIRE(t.depth() == 4);
  SECTION("with init list") {
    Lab3::Tree<int> emptyList{};
    REQUIRE(emptyList.empty());

    Lab3::Tree<int> tree{1, 2, 23, 4};
    REQUIRE(tree.length() == 4);
    REQUIRE(tree.root()->data() == 1);
    REQUIRE(tree.root()->left()->data() == 2);
    REQUIRE(tree.root()->right()->data() == 23);
    REQUIRE(tree.root()->right()->left() == nullptr);
    REQUIRE(tree.root()->left()->left()->data() == 4);
    REQUIRE(tree.root()->left()->right() == nullptr);
  }

  SECTION("with post&in order") {
    std::string inDef = "BAGHDCFE";
    std::string postDef = "BHGDFECA";
    auto post = std::vector<char>(postDef.begin(), postDef.end());
    auto in = std::vector<char>(inDef.begin(), inDef.end());

    Lab3::Tree<char> tree({post, in});
    REQUIRE(tree.length() == 8);
    REQUIRE(tree.depth() == 5);
    REQUIRE(tree.root()->data() == 'A');
    std::vector<char> res;
    std::string answer = "ABCDEGFH";

    tree.levelOrderTraverse([&res](char x) { res.push_back(x); });
    REQUIRE(res == std::vector<char>(answer.begin(), answer.end()));
    res.clear();
    answer = "ABCDGHEF";
    tree.preOrderTraverse([&res](char x) { res.push_back(x); });
    REQUIRE(res == std::vector<char>(answer.begin(), answer.end()));

    std::string bullshit = "balalla";
    std::string longBullshit = "datlalaskjdfll";
    std::string sameLengthBullshit = "zzzzzzz";
    REQUIRE_THROWS_AS(
        Lab3::Tree<char>({std::vector<char>(bullshit.begin(), bullshit.end()),
                          std::vector<char>(longBullshit.begin(), longBullshit.end())}),
        std::runtime_error);
    REQUIRE_THROWS_AS(
        Lab3::Tree<char>({std::vector<char>(bullshit.begin(), bullshit.end()),
                          std::vector<char>(sameLengthBullshit.begin(), sameLengthBullshit.end())}),
        std::out_of_range);
  }

  SECTION("empty") {
    Lab3::Tree<int> tree{1, 2, 3, 46, 7, 5, 4, 3, 2, 45, 100, 6, 74, 3, 3};
    REQUIRE(!tree.empty());
    tree.clear();
    REQUIRE(tree.empty());
    REQUIRE(tree.depth() == 0);

    REQUIRE_THROWS_AS(tree.preOrderTraverse([](int x) {}), std::runtime_error);
    REQUIRE_THROWS_AS(tree.inOrderTraverse([](int x) {}), std::runtime_error);
    REQUIRE_THROWS_AS(tree.postOrderTraverse([](int x) {}), std::runtime_error);
    REQUIRE_THROWS_AS(tree.levelOrderTraverse([](int x) {}), std::runtime_error);
  }
}
TEST_CASE("Lab3/traverse", "[Lab3, Tree]") {
  Lab3::Tree<int> t{
      1, 2, 3, 4, 10, 5, 6, 7,
  };
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
    REQUIRE(t[i]->data() == i);
  }
}

TEST_CASE("Lab3/insert", "[Lab3, Tree]") {
  Lab3::Tree<int> t{1, 2, 3, 4, 5, 6, 7, 8};
  REQUIRE(t.length() == 8);
  REQUIRE_THROWS_AS(t.insert(100000, 1000000, Lab3::Tree<int>::Right()), std::runtime_error);

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
    REQUIRE(t.locate(9) == nullptr);
  }

  SECTION("from middle with two children") {
    t.remove(2);
    REQUIRE(t.length() == 8);
    std::vector<int> res;
    t.levelOrderTraverse([&res](int x) { res.push_back(x); });
    REQUIRE(res == std::vector{1, 4, 3, 8, 9, 6, 7, 5});
  }

  SECTION("from middle with only right child") {
    // a tree with only right child
    std::string post = "ABCDE";
    std::string in = "EDCBA";
    Lab3::Tree<char> tree(
        {std::vector<char>(post.begin(), post.end()), std::vector<char>(in.begin(), in.end())});
    REQUIRE(tree.length() == 5);
    REQUIRE(tree.depth() == 5);
    tree.remove(3);
    REQUIRE(tree.length() == 4);
    REQUIRE(tree.depth() == 4);
    std::vector<char> res;
    tree.levelOrderTraverse([&res](char x) { res.push_back(x); });
    auto answer = std::string{"EDCA"};
    REQUIRE(res == std::vector<char>(answer.begin(), answer.end()));
  }

  SECTION("delete from middle with only left child") {
    std::string post = "EDCBA";
    std::string in = "EDCBA";

    Lab3::Tree<char> tree(
        {std::vector<char>(post.begin(), post.end()), std::vector<char>(in.begin(), in.end())});
    tree.remove(3);
    REQUIRE(tree.length() == 4);
    REQUIRE(tree.depth() == 4);
    std::vector<char> res;
    auto answer = std::string{"ACDE"};
    tree.levelOrderTraverse([&res](char x) { res.push_back(x); });

    REQUIRE(res == std::vector<char>(answer.begin(), answer.end()));

    Lab3::Tree<int> fancyTree({std::vector{1, 2, 3, 4, 5, 6}, {6, 5, 4, 3, 2, 1}});
  }
}
