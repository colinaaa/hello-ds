#include "Logger.hh"

#include <fmt/format.h>
#include <fmt/printf.h>

#include <iostream>

void Project::Logger::log(std::string& name) { log(std::forward<std::string>(name), "", 0); }

void Project::Logger::log(std::string& name, int childNumber) {
  log(std::forward<std::string>(name), "", childNumber);
}

void Project::Logger::log(std::string& name, std::string& value) {
  log(std::forward<std::string>(name), std::forward<std::string>(value), 0);
}

void Project::Logger::log(const std::string& name, const std::string& value, int childNumber) {
  int depth = top();

  if (!value.empty()) {
    std::cout << fmt::format("{:>{}} node with value: {}\n", name, depth, value);
  } else {
    std::cout << fmt::format("{:>{}} node\n", name, depth);
  }
  while (childNumber != 0) {
    _s.push(depth + 2);
    childNumber--;
  }
}
