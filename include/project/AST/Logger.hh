#ifndef PROJECT_LOGGER_HH
#define PROJECT_LOGGER_HH

#include <iostream>
#include <stack>

namespace Project {
class Logger {
 private:
  std::stack<int> _s;
  const int defaultLength = 8;

 public:
  void log(std::string&);
  void log(std::string&, int);
  void log(std::string&, std::string&);

 private:
  void log(const std::string&, const std::string&, int);
  inline int top() {
    if (_s.empty()) {
      return defaultLength;
    }
    int t = _s.top();
    _s.pop();
    return t;
  }

 public:
  // Logger() { _s.push(4); }
};  // class Logger
}  // namespace Project
#endif  // PROJECT_LOGGER_HH
