#include <fmt/printf.h>

#include "Parser.hh"

using fmt::printf;

void Project::Parser::expr(int lev) {
  int t, *d, *b;

  if (tk == 0) {
    printf("%d: unexpected eof in expression\n", line);
    exit(-1);
  } else if (tk == Num) {
    *--n = ival;
    *--n = Num;
    next();
    ty = INT;
  } else if (tk == '"') {
    *--n = ival;
    *--n = Num;
    next();
    while (tk == '"') next();
    data = (char *)((int)data + sizeof(int) & -sizeof(int));
    ty = PTR;
  } else if (tk == Sizeof) {
    next();
    if (tk == '(')
      next();
    else {
      printf("%d: open paren expected in sizeof\n", line);
      exit(-1);
    }
    ty = INT;
    if (tk == Int)
      next();
    else if (tk == Char) {
      next();
      ty = CHAR;
    }
    while (tk == Mul) {
      next();
      ty = ty + PTR;
    }
    if (tk == ')')
      next();
    else {
      printf("%d: close paren expected in sizeof\n", line);
      exit(-1);
    }
    *--n = (ty == CHAR) ? sizeof(char) : sizeof(int);
    *--n = Num;
    ty = INT;
  } else if (tk == Id) {
    d = id;
    next();
    if (tk == '(') {
      if (d[Class] != Sys && d[Class] != Fun) {
        printf("%d: bad function call\n", line);
        exit(-1);
      }
      next();
      t = 0;
      b = 0;
      while (tk != ')') {
        expr(Assign);
        *--n = (int)b;
        b = n;
        ++t;
        if (tk == ',') next();
      }
      next();
      *--n = t;
      *--n = d[Val];
      *--n = (int)b;
      *--n = d[Class];
      ty = d[Type];
    } else if (d[Class] == Num) {
      *--n = d[Val];
      *--n = Num;
      ty = INT;
    } else {
      if (d[Class] == Loc) {
        *--n = d[Val];
        *--n = Loc;
      } else if (d[Class] == Glo) {
        *--n = d[Val];
        *--n = Num;
      } else {
        printf("%d: undefined variable\n", line);
        exit(-1);
      }
      *--n = ty = d[Type];
      *--n = Load;
    }
  } else if (tk == '(') {
    next();
    if (tk == Int || tk == Char) {
      t = (tk == Int) ? INT : CHAR;
      next();
      while (tk == Mul) {
        next();
        t = t + PTR;
      }
      if (tk == ')')
        next();
      else {
        printf("%d: bad cast\n", line);
        exit(-1);
      }
      expr(Inc);
      ty = t;
    } else {
      expr(Assign);
      if (tk == ')')
        next();
      else {
        printf("%d: close paren expected\n", line);
        exit(-1);
      }
    }
  } else if (tk == Mul) {
    next();
    expr(Inc);
    if (ty > INT)
      ty = ty - PTR;
    else {
      printf("%d: bad dereference\n", line);
      exit(-1);
    }
    *--n = ty;
    *--n = Load;
  } else if (tk == And) {
    next();
    expr(Inc);
    if (*n == Load)
      n = n + 2;
    else {
      printf("%d: bad address-of\n", line);
      exit(-1);
    }
    ty = ty + PTR;
  } else if (tk == '!') {
    next();
    expr(Inc);
    if (*n == Num)
      n[1] = !n[1];
    else {
      *--n = 0;
      *--n = Num;
      --n;
      *n = (int)(n + 3);
      *--n = Eq;
    }
    ty = INT;
  } else if (tk == '~') {
    next();
    expr(Inc);
    if (*n == Num)
      n[1] = ~n[1];
    else {
      *--n = -1;
      *--n = Num;
      --n;
      *n = (int)(n + 3);
      *--n = Xor;
    }
    ty = INT;
  } else if (tk == Add) {
    next();
    expr(Inc);
    ty = INT;
  } else if (tk == Sub) {
    next();
    expr(Inc);
    if (*n == Num)
      n[1] = -n[1];
    else {
      *--n = -1;
      *--n = Num;
      --n;
      *n = (int)(n + 3);
      *--n = Mul;
    }
    ty = INT;
  } else if (tk == Inc || tk == Dec) {
    t = tk;
    next();
    expr(Inc);
    if (*n == Load)
      *n = t;
    else {
      printf("%d: bad lvalue in pre-increment\n", line);
      exit(-1);
    }
  } else if (tk == For || tk == Continue) {
    // do nothing
  } else {
    printf("%d: bad expression\n", line);
    exit(-1);
  }

  while (tk >= lev) {  // "precedence climbing" or "Top Down Operator Precedence" method
    t = ty;
    b = n;
    if (tk == Assign) {
      next();
      if (*n != Load) {
        printf("%d: bad lvalue in assignment\n", line);
        exit(-1);
      }
      expr(Assign);
      *--n = (int)(b + 2);
      *--n = ty = t;
      *--n = Assign;
    } else if (tk == Cond) {
      next();
      expr(Assign);
      if (tk == ':')
        next();
      else {
        printf("%d: conditional missing colon\n", line);
        exit(-1);
      }
      d = n;
      expr(Cond);
      --n;
      *n = (int)(n + 1);
      *--n = (int)d;
      *--n = (int)b;
      *--n = Cond;
    } else if (tk == Lor) {
      next();
      expr(Lan);
      if (*n == Num && *b == Num)
        n[1] = b[1] || n[1];
      else {
        *--n = (int)b;
        *--n = Lor;
      }
      ty = INT;
    } else if (tk == Lan) {
      next();
      expr(Or);
      if (*n == Num && *b == Num)
        n[1] = b[1] && n[1];
      else {
        *--n = (int)b;
        *--n = Lan;
      }
      ty = INT;
    } else if (tk == Or) {
      next();
      expr(Xor);
      if (*n == Num && *b == Num)
        n[1] = b[1] | n[1];
      else {
        *--n = (int)b;
        *--n = Or;
      }
      ty = INT;
    } else if (tk == Xor) {
      next();
      expr(And);
      if (*n == Num && *b == Num)
        n[1] = b[1] ^ n[1];
      else {
        *--n = (int)b;
        *--n = Xor;
      }
      ty = INT;
    } else if (tk == And) {
      next();
      expr(Eq);
      if (*n == Num && *b == Num)
        n[1] = b[1] & n[1];
      else {
        *--n = (int)b;
        *--n = And;
      }
      ty = INT;
    } else if (tk == Eq) {
      next();
      expr(Lt);
      if (*n == Num && *b == Num)
        n[1] = b[1] == n[1];
      else {
        *--n = (int)b;
        *--n = Eq;
      }
      ty = INT;
    } else if (tk == Ne) {
      next();
      expr(Lt);
      if (*n == Num && *b == Num)
        n[1] = b[1] != n[1];
      else {
        *--n = (int)b;
        *--n = Ne;
      }
      ty = INT;
    } else if (tk == Lt) {
      next();
      expr(Shl);
      if (*n == Num && *b == Num)
        n[1] = b[1] < n[1];
      else {
        *--n = (int)b;
        *--n = Lt;
      }
      ty = INT;
    } else if (tk == Gt) {
      next();
      expr(Shl);
      if (*n == Num && *b == Num)
        n[1] = b[1] > n[1];
      else {
        *--n = (int)b;
        *--n = Gt;
      }
      ty = INT;
    } else if (tk == Le) {
      next();
      expr(Shl);
      if (*n == Num && *b == Num)
        n[1] = b[1] <= n[1];
      else {
        *--n = (int)b;
        *--n = Le;
      }
      ty = INT;
    } else if (tk == Ge) {
      next();
      expr(Shl);
      if (*n == Num && *b == Num)
        n[1] = b[1] >= n[1];
      else {
        *--n = (int)b;
        *--n = Ge;
      }
      ty = INT;
    } else if (tk == Shl) {
      next();
      expr(Add);
      if (*n == Num && *b == Num)
        n[1] = b[1] << n[1];
      else {
        *--n = (int)b;
        *--n = Shl;
      }
      ty = INT;
    } else if (tk == Shr) {
      next();
      expr(Add);
      if (*n == Num && *b == Num)
        n[1] = b[1] >> n[1];
      else {
        *--n = (int)b;
        *--n = Shr;
      }
      ty = INT;
    } else if (tk == Add) {
      next();
      expr(Mul);
      if ((ty = t) > PTR) {
        if (*n == Num)
          n[1] = n[1] * sizeof(int);
        else {
          *--n = sizeof(int);
          *--n = Num;
          --n;
          *n = (int)(n + 3);
          *--n = Mul;
        }
      }
      if (*n == Num && *b == Num)
        n[1] = b[1] + n[1];
      else {
        *--n = (int)b;
        *--n = Add;
      }
    } else if (tk == Sub) {
      next();
      expr(Mul);
      if ((ty = t) > PTR) {
        if (*n == Num)
          n[1] = n[1] * sizeof(int);
        else {
          *--n = sizeof(int);
          *--n = Num;
          --n;
          *n = (int)(n + 3);
          *--n = Mul;
        }
      }
      if (*n == Num && *b == Num)
        n[1] = b[1] - n[1];
      else {
        *--n = (int)b;
        *--n = Sub;
      }
    } else if (tk == Mul) {
      next();
      expr(Inc);
      if (*n == Num && *b == Num)
        n[1] = b[1] * n[1];
      else {
        *--n = (int)b;
        *--n = Mul;
      }
      ty = INT;
    } else if (tk == Div) {
      next();
      expr(Inc);
      if (*n == Num && *b == Num)
        n[1] = b[1] / n[1];
      else {
        *--n = (int)b;
        *--n = Div;
      }
      ty = INT;
    } else if (tk == Mod) {
      next();
      expr(Inc);
      if (*n == Num && *b == Num)
        n[1] = b[1] % n[1];
      else {
        *--n = (int)b;
        *--n = Mod;
      }
      ty = INT;
    } else if (tk == Inc || tk == Dec) {
      if (*n == Load)
        *n = tk;
      else {
        printf("%d: bad lvalue in post-increment\n", line);
        exit(-1);
      }
      *--n = (ty > PTR) ? sizeof(int) : sizeof(char);
      *--n = Num;
      *--n = (int)b;
      *--n = (tk == Inc) ? Sub : Add;
      next();
    } else if (tk == Brak) {
      next();
      expr(Assign);
      if (tk == ']')
        next();
      else {
        printf("%d: close bracket expected\n", line);
        exit(-1);
      }
      if (t > PTR) {
        if (*n == Num)
          n[1] = n[1] * sizeof(int);
        else {
          *--n = sizeof(int);
          *--n = Num;
          --n;
          *n = (int)(n + 3);
          *--n = Mul;
        }
      } else if (t < PTR) {
        printf("%d: pointer type expected\n", line);
        exit(-1);
      }
      if (*n == Num && *b == Num)
        n[1] = b[1] + n[1];
      else {
        *--n = (int)b;
        *--n = Add;
      }
      *--n = ty = t - PTR;
      *--n = Load;
    } else {
      printf("%d: compiler error tk=%d\n", line, tk);
      exit(-1);
    }
  }
}
