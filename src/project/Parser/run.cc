#include <fcntl.h>
#include <fmt/printf.h>
#include <unistd.h>

#define MAGIC_ENUM_RANGE_MAX 256
#define MAGIC_ENUM_RANGE_MIN 0
#include <magic_enum.hpp>

#include "Parser.hh"

using fmt::printf;

inline auto Project::Parser::tokenName(int tk) {
  return magic_enum::enum_name(static_cast<Token>(tk));
}

auto Project::Parser::run(const std::string& filename) -> int {
  int fd, bt, *idmain, *ast;
  int i, *t;  // temps
  // setup keywords and library functions
  static char keywords[] = "char else enum if int return sizeof for continue break while";
  static char library[] = "open read close printf malloc free memset memcmp exit void main";

  p = keywords;
  i = Char;
  while (i <= While) {
    next();
    id[Tk] = i++;
  }  // add keywords to symbol table

  p = library;
  i = OPEN;
  while (i <= EXIT) {
    next();
    id[Class] = Sys;
    id[Type] = INT;
    id[Val] = i++;
  }  // add library to symbol table

  next();
  id[Tk] = Char;  // handle void type
  next();
  idmain = id;  // keep track of main

  if (!(lp = p = static_cast<char*>(malloc(poolSize)))) {
    printf("could not malloc(%d) source area\n", poolSize);
    return -1;
  }
  if ((fd = open(filename.c_str(), 0)) < 0) {
    printf("could not open(%s)\n", filename.c_str());
    return -1;
  }
  if ((i = read(fd, p, poolSize - 1)) <= 0) {
    printf("read() returned %d\n", i);
    return -1;
  }
  if (!(ast = static_cast<int*>(malloc(poolSize)))) {
    printf("could not malloc(%d) abstract syntax tree area\n", poolSize);
    return -1;
  }
  ast = (int*)((int)ast + poolSize);  // abstract syntax tree is most efficiently built as a stack

  p[i] = 0;
  close(fd);

  // parse declarations
  line = 1;
  next();
  while (tk) {
    bt = INT;  // basetype
    if (tk == Int)
      next();
    else if (tk == Char) {
      next();
      bt = CHAR;
    } else if (tk == Enum) {
      next();
      if (tk != '{') next();
      if (tk == '{') {
        next();
        i = 0;
        while (tk != '}') {
          if (tk != Id) {
            auto token = tokenName(tk);
            printf("%d: bad enum identifier: is %s\n", line, token);
            return -1;
          }
          next();
          if (tk == Assign) {
            next();
            n = ast;
            expr(Cond);
            if (*n != Num) {
              printf("%d: bad enum initializer: is not Num\n", line);
              return -1;
            }
            i = n[1];
          }
          id[Class] = Num;
          id[Type] = INT;
          id[Val] = i++;
          if (tk == ',') next();
        }
        next();
      }
    }
    while (tk != ';' && tk != '}') {
      ty = bt;
      while (tk == Mul) {
        next();
        ty = ty + PTR;
      }
      if (tk != Id) {
        auto token = tokenName(tk);
        printf("%d: bad global declaration: token is %s, not Identifier\n", line, token);
        return -1;
      }
      if (id[Class]) {
        auto name = getFuncName(reinterpret_cast<char*>(id[Name]));
        printf("%d: duplicate global definition: %s\n", line, name);
        return -1;
      }
      next();
      id[Type] = ty;
      if (tk == '(') {  // function
        id[Class] = Fun;
        id[Val] = (int)(e + 1);
        next();
        i = 2;
        while (tk != ')') {
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
          if (tk != Id) {
            auto token = magic_enum::enum_name(static_cast<Token>(tk));
            printf("%d: bad parameter declaration, token is not identifiers but %s\n", line, token);
            return -1;
          }
          if (id[Class] == Loc) {
            auto name = getParamName(reinterpret_cast<char*>(id[Name]));
            printf("%d: duplicate parameter definition: %s\n", line, name);
            return -1;
          }
          id[HClass] = id[Class];
          id[Class] = Loc;
          id[HType] = id[Type];
          id[Type] = ty;
          id[HVal] = id[Val];
          id[Val] = i++;
          next();
          if (tk == ',') next();
        }
        next();
        if (tk != '{') {
          printf("%d: bad function definition\n", line);
          return -1;
        }
        i = 0;
        next();
        while (tk == Int || tk == Char) {
          bt = (tk == Int) ? INT : CHAR;
          next();
          while (tk != ';') {
            ty = bt;
            while (tk == Mul) {
              next();
              ty = ty + PTR;
            }
            if (tk != Id) {
              printf("%d: bad local declaration with tk=%d\n", line, tk);
              return -1;
            }
            if (id[Class] == Loc) {
              printf("%d: duplicate local definition\n", line);
              return -1;
            }
            id[HClass] = id[Class];
            id[Class] = Loc;
            id[HType] = id[Type];
            id[Type] = ty;
            id[HVal] = id[Val];
            id[Val] = --i;
            next();
            if (tk == ',') next();
          }
          next();
        }
        n = ast;
        *--n = ';';
        while (tk != '}') {
          t = n;
          stmt();
          *--n = (int)t;
          *--n = '{';
        }
        *--n = -i;
        *--n = Enter;
        gen(n);
        id = sym;  // unwind symbol table locals
        while (id[Tk]) {
          if (id[Class] == Loc) {
            id[Class] = id[HClass];
            id[Type] = id[HType];
            id[Val] = id[HVal];
          }
          id = id + Idsz;
        }
      } else {
        id[Class] = Glo;
        id[Val] = (int)data;
        data = data + sizeof(int);
      }
      if (tk == ',') next();
    }
    next();
  }

  if (((int*)idmain[Val]) == nullptr) {
    printf("main() not defined\n");
    return -1;
  }
  return 0;
}
