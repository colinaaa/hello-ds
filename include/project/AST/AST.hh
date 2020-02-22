#ifndef AST_HH
#define AST_HH

#include <string>
#include <vector>

namespace Project {

class Node {
 private:
  std::string name;

 public:
  void printName(std::string&&);
  virtual void printName() = 0;
  void addChild(Node&);
  Node(std::string&&, int);

 private:
  std::vector<Node> children;

 public:
  inline auto depth() -> int { return _depth; }

 private:
  int _depth;
};  // class Node

class StmtNode : public Node {
 private:
 public:
  StmtNode(std::string&&, int);
  void printName() override;
};  // class StmtNode

class ExprNode : public Node {
 private:
  bool binary{};

 public:
  ExprNode(std::string&&, int);
  void printName() override;
};  // class ExprNode

class IdenNode : private Node {
 private:
  int type{};

 public:
  IdenNode(std::string&&, int);
  void printName() override;
};  // class IdenNode

class CostNode : public Node {
 private:
  int type{};

 public:
  CostNode(std::string&&, int);
  void printName() override;

};  // class IdenNode

}  // namespace Project

#endif  // AST_HH
