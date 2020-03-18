#include <utility>

#include "Parser.hh"

void Project::Parser::log(const std::string&& name, int childNumber) {
  if (!tree) return;
  logger.log(name, childNumber);
}

void Project::Parser::log(const std::string&& name) {
  log(std::forward<const std::string>(name), 0);
}
