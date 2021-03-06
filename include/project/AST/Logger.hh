#ifndef PROJECT_LOGGER_HH
#define PROJECT_LOGGER_HH

#include <iostream>
#include <stack>

namespace Project {
class Logger {
 private:
  std::stack<int> s;
  const int defaultLength = 0;
  int indent = 2;

 public:
  void log(const std::string&);
  void log(const std::string&, int);

 private:
  inline int top() {
    if (s.empty()) {
      return defaultLength;
    }
    int t = s.top();
    s.pop();
    return t;
  }

 public:
  Logger(const int indent = 2) : indent(indent) {}
  inline void setIndent(int idt) { indent = idt; }

};  // class Logger
}  // namespace Project
#endif  // PROJECT_LOGGER_HH
