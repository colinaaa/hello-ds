#include "Logger.hh"

#include <fmt/format.h>
#include <fmt/printf.h>

#include <iostream>

void Project::Logger::log(const std::string& name) {
  log(std::forward<const std::string>(name), 0);
}

void Project::Logger::log(const std::string& name, int childNumber) {
  int depth = top();

  std::cout << fmt::format("{:>{}} node\n", name, depth + name.size());

  while (childNumber != 0) {
    s.push(depth + indent);
    childNumber--;
  }
}
