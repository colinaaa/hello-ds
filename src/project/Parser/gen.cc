#include <fmt/format.h>
#include <fmt/printf.h>

#include "Parser.hh"

void Project::Parser::gen(int *n) {
  int i, *a, *b;

  i = *n;
  if (i == Num) {
    log(fmt::format("Number {}({:#04x})", n[1], n[1]));
  } else if (i == Loc) {
    // local variable
    log("Local var");
  } else if (i == Load) {
    gen(n + 2);
  } else if (i == Assign) {
    log("Assign", 2);
    gen((int *)n[2]);
    gen(n + 3);
  } else if (i == Inc || i == Dec) {
    // operator ++; operator --
    log("Inc/Dec", 1);
    gen(n + 2);
  } else if (i == Cond) {
    log("Condition", n[3] ? 3 : 2);
    gen((int *)n[1]);
    gen((int *)n[2]);
    if (n[3]) {
      gen((int *)n[3]);
    }
  } else if (i == Lor) {
    // operator ||
    log("LogicOr", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Lan) {
    // operator &&
    log("LogicAnd", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Or) {
    // operator |
    log("BitOr", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Xor) {
    // operator ^
    log("Xor", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == And) {
    // operator &
    log("BitAnd", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Eq) {
    // operator ==
    log("Equal", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Ne) {
    // operator !=
    log("NotEqual", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Lt) {
    // operator <
    log("LessThan", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Gt) {
    // operator >
    log("GreaterThan", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Le) {
    // operator <=
    log("LessOrEqual", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Ge) {
    // operator >=
    log("GreaterOrEqual", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Shl) {
    // operator <<
    log("ShiftLeft", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Shr) {
    // operator >>
    log("ShiftRight", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Add) {
    // operator +
    log("Add", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Sub) {
    // operator -
    log("Minus", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Mul) {
    // operator *
    log("Multiply", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Div) {
    // operator *
    log("Divide", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Mod) {
    // operator %
    log("Mod", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Sys || i == Fun) {
    int count = 0;
    b = (int *)n[1];
    while (b) {
      count++;
      b = (int *)*b;
    }
    log("FunctionCall", count);
    b = (int *)n[1];
    while (b) {
      gen(b + 1);
      b = (int *)*b;
    }
  } else if (i == For) {
  } else if (i == While) {
    log("While", 2);
    gen(n + 2);
    gen((int *)n[1]);
  } else if (i == Return) {
    log("Return", n[1] ? 1 : 0);
    if (n[1]) gen((int *)n[1]);
  } else if (i == '{') {
    // log("Block", 2);
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Break) {
  } else if (i == Continue) {
  } else if (i == Enter) {
    // TODO: what is this
    gen(n + 2);
  } else if (i != ';') {
    printf("%d: compiler error gen=%d\n", line, i);
    exit(-1);
  }
}
