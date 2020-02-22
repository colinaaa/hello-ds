#include "Parser.hh"
void Project::Parser::gen(int *n) {
  int i, *a, *b;

  i = *n;
  if (i == Num) {
    *++e = IMM;
    *++e = n[1];
  } else if (i == Loc) {
    *++e = LEA;
    *++e = n[1];
  } else if (i == Load) {
    gen(n + 2);
    *++e = (n[1] == CHAR) ? LC : LI;
  } else if (i == Assign) {
    gen((int *)n[2]);
    *++e = PSH;
    gen(n + 3);
    *++e = (n[1] == CHAR) ? SC : SI;
  } else if (i == Inc || i == Dec) {
    gen(n + 2);
    *++e = PSH;
    *++e = (n[1] == CHAR) ? LC : LI;
    *++e = PSH;
    *++e = IMM;
    *++e = (n[1] > PTR) ? sizeof(int) : sizeof(char);
    *++e = (i == Inc) ? ADD : SUB;
    *++e = (n[1] == CHAR) ? SC : SI;
  } else if (i == Cond) {
    gen((int *)n[1]);
    *++e = BZ;
    b = ++e;
    gen((int *)n[2]);
    if (n[3]) {
      *b = (int)(e + 3);
      *++e = JMP;
      b = ++e;
      gen((int *)n[3]);
    }
    *b = (int)(e + 1);
  } else if (i == Lor) {
    gen((int *)n[1]);
    *++e = BNZ;
    b = ++e;
    gen(n + 2);
    *b = (int)(e + 1);
  } else if (i == Lan) {
    gen((int *)n[1]);
    *++e = BZ;
    b = ++e;
    gen(n + 2);
    *b = (int)(e + 1);
  } else if (i == Or) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = OR;
  } else if (i == Xor) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = XOR;
  } else if (i == And) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = AND;
  } else if (i == Eq) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = EQ;
  } else if (i == Ne) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = NE;
  } else if (i == Lt) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = LT;
  } else if (i == Gt) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = GT;
  } else if (i == Le) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = LE;
  } else if (i == Ge) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = GE;
  } else if (i == Shl) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = SHL;
  } else if (i == Shr) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = SHR;
  } else if (i == Add) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = ADD;
  } else if (i == Sub) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = SUB;
  } else if (i == Mul) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = MUL;
  } else if (i == Div) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = DIV;
  } else if (i == Mod) {
    gen((int *)n[1]);
    *++e = PSH;
    gen(n + 2);
    *++e = MOD;
  } else if (i == Sys || i == Fun) {
    b = (int *)n[1];
    while (b) {
      gen(b + 1);
      *++e = PSH;
      b = (int *)*b;
    }
    if (i == Fun) *++e = JSR;
    *++e = n[2];
    if (n[3]) {
      *++e = ADJ;
      *++e = n[3];
    }
  } else if (i == While) {
    *++e = JMP;
    b = ++e;
    gen(n + 2);
    *b = (int)(e + 1);
    gen((int *)n[1]);
    *++e = BNZ;
    *++e = (int)(b + 1);
  } else if (i == Return) {
    if (n[1]) gen((int *)n[1]);
    *++e = LEV;
  } else if (i == '{') {
    gen((int *)n[1]);
    gen(n + 2);
  } else if (i == Enter) {
    *++e = ENT;
    *++e = n[1];
    gen(n + 2);
    *++e = LEV;
  } else if (i != ';') {
    printf("%d: compiler error gen=%d\n", line, i);
    exit(-1);
  }
}
