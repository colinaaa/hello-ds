#include <fmt/printf.h>

#include "Parser.hh"

using fmt::printf;

void Project::Parser::stmt() {
  int *a, *b, *c;

  if (tk == If) {
    next();
    if (tk == '(') {
      next();
    } else {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    a = n;
    if (tk == ')') {
      next();
    } else {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    stmt();
    b = n;
    if (tk == Else) {
      next();
      stmt();
      c = n;
    } else {
      c = 0;
    }
    *--n = reinterpret_cast<int>(c);
    *--n = reinterpret_cast<int>(b);
    *--n = reinterpret_cast<int>(a);
    *--n = Cond;
  } else if (tk == For) {
    next();
    if (tk == '(') {
      next();
    } else {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    a = n;
    if (tk == ';') {
      next();
    } else {
      printf("%d semicolon expected\n", line);
      exit(-1);
    }
    expr(Assign);
    b = n;
    if (tk == ';') {
      next();
    } else {
      printf("%d semicolon expected\n", line);
      exit(-1);
    }
    expr(Assign);
    c = n;
    if (tk == ')') {
      next();
    } else {
      printf("%d: close paren expected\n", line);
    }
    stmt();
    *--n = reinterpret_cast<int>(a);
    *--n = reinterpret_cast<int>(b);
    *--n = reinterpret_cast<int>(c);
    *--n = For;
  } else if (tk == While) {
    next();
    if (tk == '(') {
      next();
    } else {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    a = n;
    if (tk == ')') {
      next();
    } else {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    stmt();
    *--n = reinterpret_cast<int>(a);
    *--n = While;
  } else if (tk == Return) {
    next();
    if (tk != ';') {
      expr(Assign);
      a = n;
    } else {
      a = nullptr;
    }
    if (tk == ';') {
      next();
    } else {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
    *--n = reinterpret_cast<int>(a);
    *--n = Return;
  } else if (tk == '{') {
    int count;
    count = 0;
    next();
    b = --n;
    *--n = '[';
    while (tk != '}') {
      a = n;
      stmt();
      *--n = reinterpret_cast<int>(a);
      *--n = '{';
      ++count;
    }
    *b = count;
    next();
  } else if (tk == ';') {
    next();
    *--n = ';';
  } else if (tk == Continue) {
    next();
    if (tk != ';') {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
    a = nullptr;
    *--n = reinterpret_cast<int>(a);
    *--n = Continue;
  } else if (tk == Break) {
    next();
    if (tk != ';') {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
    a = nullptr;
    *--n = reinterpret_cast<int>(a);
    *--n = Break;
  } else {
    expr(Assign);
    if (tk == ';')
      next();
    else {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
  }
}
