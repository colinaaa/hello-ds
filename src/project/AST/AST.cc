#include "AST.hh"

void Project::Node::printName(std::string&& n) {
  for (int i = 0; i < _depth; i++) {
    n += "\t";
  }
  printf("%s Node %s\n", n.c_str(), name.c_str());
}

Project::Node::Node(std::string&& name, int depth)
    : name(name), _depth(depth), children(std::vector<Node>()){};

void Project::Node::addChild(Node& c) { children.push_back(c); }

void Project::StmtNode::printName() { Node::printName("statemt"); }

void Project::ExprNode::printName() { Node::printName("expression"); }

void Project::IdenNode::printName() { Node::printName("identifier"); }

void Project::CostNode::printName() { Node::printName("constance"); }

Project::StmtNode::StmtNode(std::string&& name, int depth) : Node(std::move(name), depth){};

Project::ExprNode::ExprNode(std::string&& name, int depth) : Node(std::move(name), depth){};

Project::IdenNode::IdenNode(std::string&& name, int depth) : Node(std::move(name), depth){};

Project::CostNode::CostNode(std::string&& name, int depth) : Node(std::move(name), depth){};

