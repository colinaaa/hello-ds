#ifndef PROJECT_PARSER_HH
#define PROJECT_PARSER_HH

#include <fcntl.h>
#include <memory.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include "AST/Logger.hh"
#define int long long

namespace Project {
class Parser {
 private:
  char *p{}, *lp = nullptr,  // current position in source code
      *data{};               // data/bss pointer

  int *e,
      *le;  // current position in emitted code

  int *id = nullptr,  // currently parsed identifier
      *n = nullptr,   // node of ast tree
      *sym,           // symbol table (simple list of identifiers)
      tk = 0,         // current token
      ival = 0,       // current token value
      ty = 0,         // current expression type
      loc = 0,        // local variable offset
      line,           // current line number

      src,    // print source and assembly flag
      debug;  // print executed instructions

  // tokens and classes (operators last and in precedence order)
  enum {
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
  enum {
    LEA,
    IMM,
    JMP,
    JSR,
    BZ,
    BNZ,
    ENT,
    ADJ,
    LEV,
    LI,
    LC,
    SI,
    SC,
    PSH,
    OR,
    XOR,
    AND,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    SHL,
    SHR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    OPEN,
    READ,
    CLOS,
    PRTF,
    MALC,
    FREE,
    MSET,
    MCMP,
    EXIT
  };

 private:
  // types
  enum { CHAR, INT, PTR };

  // identifier offsets
  enum { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };
  int poolSize = 256 * 1024;

 public:
  void next();
  void expr(int);
  void stmt();
  void gen(int *);

  auto run(const std::string &) -> int;

 public:
  Parser();
  inline void setSrc(const int v = 1) noexcept { src = v; }
  inline void setDebug(const int v = 1) noexcept { debug = v; }

 private:
  Logger logger;
  // node only with name
  void log(std::string&&);
  // node with child number
  void log(std::string&&, int);
  // node with value
  void log(std::string&&, std::string&&);
};

}  // namespace Project

#endif  // PROJECT_PARSER_HH
