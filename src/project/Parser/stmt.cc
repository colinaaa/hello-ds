#include "Parser.hh"

void Project::Parser::stmt() {
  int *a, *b, *c;

  if (tk == If) {
    next();
    if (tk == '(')
      next();
    else {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    a = n;
    if (tk == ')')
      next();
    else {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    stmt();
    b = n;
    if (tk == Else) {
      next();
      stmt();
      c = n;
    } else
      c = 0;
    *--n = (int)c;
    *--n = (int)b;
    *--n = (int)a;
    *--n = Cond;
  } else if (tk == While) {
    next();
    if (tk == '(')
      next();
    else {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    a = n;
    if (tk == ')')
      next();
    else {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    stmt();
    *--n = (int)a;
    *--n = While;
  } else if (tk == Return) {
    next();
    if (tk != ';') {
      expr(Assign);
      a = n;
    } else
      a = 0;
    if (tk == ';')
      next();
    else {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
    *--n = (int)a;
    *--n = Return;
  } else if (tk == '{') {
    next();
    *--n = ';';
    while (tk != '}') {
      a = n;
      stmt();
      *--n = (int)a;
      *--n = '{';
    }
    next();
  } else if (tk == ';') {
    next();
    *--n = ';';
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
