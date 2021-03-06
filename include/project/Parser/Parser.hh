#ifndef PROJECT_PARSER_HH
#define PROJECT_PARSER_HH

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>

#include "AST/Logger.hh"
#define int long long

namespace Project {
class Parser {
 private:
  char *p{}, *lp = nullptr,  // current position in source code
      *data{};               // data pointer
  char *db;

  int *e, *eb;

  int *id = nullptr,  // currently parsed identifier
      *n = nullptr,   // node of AST tree
      *sym,           // symbol table
      tk = 0,         // current token
      ival = 0,       // current token value
      ty = 0,         // current expression type
      line;           // current line number

  // tokens and classes (operators last and in precedence order)
 public:
  enum Token {
    Num = 128,
    Fun,
    Sys,
    Glo,
    Loc,
    Id,
    Load,
    Enter,
    Char,
    Else,
    Enum,
    If,
    Int,
    Return,
    Sizeof,
    For,
    Continue,
    Break,
    While,
    Assign,
    Cond,
    Lor,
    Lan,
    Or,
    Xor,
    And,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    Shl,
    Shr,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Inc,
    Dec,
    Brak
  };

  // operators codes
  enum Operator { OPEN, READ, CLOS, PRTF, MALC, FREE, MSET, MCMP, EXIT };

  // types
  enum Type { CHAR, INT, PTR };

  // identifier offsets
  enum Offset { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };

 private:
  int poolSize = 256 * 1024;

 public:
  void next();
  void expr(int);
  void stmt();
  void gen(int *);

  auto run(const std::string &) -> int;

 private:
  bool src = false;     // print source
  bool debug = false;   // print executed instructions
  bool tree = false;    // print AST tree
  bool output = false;  // output to file

  std::string outputFileName = "out.c";
  std::ofstream out;

 public:
  Parser();
  ~Parser();
  inline void setSrc(const bool v = true) noexcept { src = v; }
  inline void setDebug(const bool v = true) noexcept { debug = v; }
  inline void setTree(const bool v = true) noexcept { tree = v; }
  inline void setIndent(const int v) noexcept { logger.setIndent(v); }
  inline void setOutputName(const std::string &v) { outputFileName = v; }
  inline void setOutput(const bool v = true) { output = v; }

 private:
  Logger logger;
  // node only with name
  void log(const std::string &&);
  // node with child number
  void log(const std::string &&, int);
  static inline auto getTokenName(char *name, char delimit) {
    auto identifier = std::string{name};
    return identifier.substr(0, identifier.find_first_of(delimit));
  }
  static inline auto getFuncName(char *name) { return getTokenName(name, '('); }
  static inline auto getParamName(char *name) { return getTokenName(name, ','); }

  static inline auto tokenName(int tk);

 public:
  inline auto parseToken(std::string &t) {
    p = t.data();
    next();
    return tk;
  }
};

}  // namespace Project

#endif  // PROJECT_PARSER_HH
