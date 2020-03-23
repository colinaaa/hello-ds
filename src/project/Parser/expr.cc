#include <fmt/printf.h>

#define MAGIC_ENUM_RANGE_MAX 256
#define MAGIC_ENUM_RANGE_MIN 0
#include <magic_enum.hpp>

#include "Parser.hh"

using fmt::printf;

// expr - Parse expression
//    Arg: lev  the current operator precedence
void Project::Parser::expr(int lev) {
  int t, *d, *b;

  if (tk == 0) {
    printf("%d: unexpected eof in expression\n", line);
    exit(-1);
  } else if (tk == Num) {
    // number
    *--n = ival;
    *--n = Num;
    next();
    ty = INT;
  } else if (tk == '"') {
    // string
    *--n = ival;
    *--n = Num;
    next();
    // While current token is string constant, it is adjacent string
    // constants, e.g. "abc" "def".
    while (tk == '"') next();
    // Point `data` to next int-aligned address.
    // This guarantees to leave at least one '\0' after the string.
    data = reinterpret_cast<char *>(reinterpret_cast<int>(data) + sizeof(int) & -sizeof(int));

    // Set result value type be char pointer.
    ty = PTR;
  } else if (tk == Sizeof) {
    // If current token is `(`, read token, else print error and exit
    // program.
    next();
    if (tk == '(') {
      next();
    } else {
      printf("%d: open paren expected in sizeof\n", line);
      exit(-1);
    }
    ty = INT;
    if (tk == Int) {
      next();
    } else if (tk == Char) {
      next();
      ty = CHAR;
    }

    // While current token is `*`, it is pointer type.
    // Add `PTR` to the operand value type.
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
    // identifier
    d = id;
    next();
    if (tk == '(') {
      // function call
      if (d[Class] != Sys && d[Class] != Fun) {
        printf("%d: bad function call\n", line);
        exit(-1);
      }
      next();
      t = 0;  // arg count
      b = 0;  // base addr
      // Parse argument.
      while (tk != ')') {
        expr(Assign);
        *--n = (int)b;
        b = n;
        ++t;
        if (tk == ',') next();
      }
      // Skip `)`.
      next();
      *--n = t;
      *--n = d[Val];
      // Store base address.
      *--n = reinterpret_cast<int>(b);
      *--n = d[Class];
      // Set result value type be the system call or function's return type.
      ty = d[Type];
    } else if (d[Class] == Num) {
      // number
      *--n = d[Val];
      *--n = Num;
      ty = INT;
    } else {
      // variable
      if (d[Class] == Loc) {
        // Local variable.
        *--n = d[Val];
        *--n = Loc;
      } else if (d[Class] == Glo) {
        // Global variable.
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
    // Cast or expression in paren.
    next();
    if (tk == Int || tk == Char) {
      // cast
      t = (tk == Int) ? INT : CHAR;
      next();

      // While current token is `*`, it is pointer type.
      // Add `PTR` to the cast's data type.
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

      // Parse casted expression.
      // Use `Inc` to allow only `++`, `--`, `[]` operators in the expression.
      expr(Inc);
      ty = t;
    } else {
      // expr in paren
      expr(Assign);
      if (tk == ')') {
        next();
      } else {
        printf("%d: close paren expected\n", line);
        exit(-1);
      }
    }
  } else if (tk == Mul) {
    // dereference
    next();

    // Parse operand expression.
    // Use `Inc` to allow only `++`, `--`, `[]` operators in the expression.
    expr(Inc);
    if (ty > INT) {
      ty = ty - PTR;
    } else {
      printf("%d: bad dereference\n", line);
      exit(-1);
    }
    *--n = ty;
    *--n = Load;
  } else if (tk == And) {
    // address-of
    next();

    // Parse operand expression.
    // Use `Inc` to allow only `++`, `--`, `[]` operators in the expression.
    expr(Inc);
    if (*n == Load) {
      n = n + 2;
    } else {
      printf("%d: bad address-of\n", line);
      exit(-1);
    }

    // Set result value type be pointer to current value type.
    ty = ty + PTR;
  } else if (tk == '!') {
    next();

    // Parse operand expression.
    // Use `Inc` to allow only `++`, `--`, `[]` operators in the expression.
    expr(Inc);
    if (*n == Num) {
      // Optimization the constant to it's negative.
      n[1] = !n[1];
    } else {
      // Can not optimize.
      *--n = 0;
      *--n = Num;
      --n;
      *n = reinterpret_cast<int>(n + 3);
      *--n = Eq;
    }
    ty = INT;
  } else if (tk == '~') {
    // similar as before
    next();
    expr(Inc);
    if (*n == Num) {
      // Optimization
      n[1] = ~n[1];
    } else {
      *--n = -1;
      *--n = Num;
      --n;
      *n = reinterpret_cast<int>(n + 3);
      *--n = Xor;
    }
    ty = INT;
  } else if (tk == Add) {
    // Do nothing due to `+` has no effect.
    next();
    expr(Inc);
    ty = INT;
  } else if (tk == Sub) {
    // same as before
    next();
    expr(Inc);
    if (*n == Num) {
      // Optimization
      n[1] = -n[1];
    } else {
      *--n = -1;
      *--n = Num;
      --n;
      *n = reinterpret_cast<int>(n + 3);
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
          *n = reinterpret_cast<int>(n + 3);
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
          *n = reinterpret_cast<int>(n + 3);
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
      // array subscript []
      next();
      expr(Assign);
      if (tk == ']')
        next();
      else {
        printf("%d: close bracket expected\n", line);
        exit(-1);
      }
      if (t > PTR) {
        if (*n == Num) {
          // Optimization
          n[1] = n[1] * sizeof(int);
        } else {
          *--n = sizeof(int);
          *--n = Num;
          --n;
          *n = reinterpret_cast<int>(n + 3);
          *--n = Mul;
        }
      } else if (t < PTR) {
        printf("%d: pointer type expected\n", line);
        exit(-1);
      }
      if (*n == Num && *b == Num) {
        // Optimization
        n[1] = b[1] + n[1];
      } else {
        *--n = (int)b;
        *--n = Add;
      }
      *--n = ty = t - PTR;
      *--n = Load;
    } else {
      printf("%d: compiler error tk=%d\n", line, magic_enum::enum_name(static_cast<Token>(tk)));
      exit(-1);
    }
  }
}
