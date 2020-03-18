#include <fmt/printf.h>

#include "Parser.hh"

using fmt::printf;

void Project::Parser::next() {
  char *pp;

  while ((tk = *p) != 0) {
    ++p;
    if (tk == '\n') {
      if (src != 0) {
        printf("%2d: %.*s", line, p - lp, lp);
        lp = p;
      }
      /*
       * insert into AST here
       */
      ++line;
    } else if (tk == '#') {
      // marco
      // TODO(marco): add marco
      while (*p != 0 && *p != '\n') ++p;
    } else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_') {
      // indentifier
      pp = p - 1;
      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') ||
             *p == '_') {
        tk = tk * 147 + *p++;
      }
      tk = (tk << 6) + (p - pp);
      id = sym;
      while (id[Tk] != 0) {
        if (tk == id[Hash] && (memcmp((char *)id[Name], pp, p - pp) == 0)) {
          tk = id[Tk];
          return;
        }
        id = id + Idsz;
      }
      id[Name] = (int)pp;
      id[Hash] = tk;
      tk = id[Tk] = Id;
      return;
    } else if (tk >= '0' && tk <= '9') {
      if ((ival = tk - '0') != 0) {
        while (*p >= '0' && *p <= '9') ival = ival * 10 + *p++ - '0';
      } else if (*p == 'x' || *p == 'X') {
        while ((tk = *++p) &&
               ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
          ival = (ival << 4) + (tk & 0xf) + (tk >= 'A' ? 9 : 0);
      } else {
        while (*p >= '0' && *p <= '7') ival = ival * 8 + *p++ - '0';
      }
      tk = Num;
      return;
    } else if (tk == '/') {
      if (*p == '/') {
        ++p;
        while (*p != 0 && *p != '\n') ++p;
      } else {
        tk = Div;
        return;
      }
    } else if (tk == '\'' || tk == '"') {
      pp = data;
      while (*p != 0 && *p != tk) {
        if ((ival = *p++) == '\\') {
          if ((ival = *p++) == 'n') ival = '\n';
        }
        if (tk == '"') *data++ = ival;
      }
      ++p;
      if (tk == '"')
        ival = (int)pp;
      else
        tk = Num;
      return;
    } else if (tk == '=') {
      if (*p == '=') {
        ++p;
        tk = Eq;
      } else
        tk = Assign;
      return;
    } else if (tk == '+') {
      if (*p == '+') {
        ++p;
        tk = Inc;
      } else
        tk = Add;
      return;
    } else if (tk == '-') {
      if (*p == '-') {
        ++p;
        tk = Dec;
      } else
        tk = Sub;
      return;
    } else if (tk == '!') {
      if (*p == '=') {
        ++p;
        tk = Ne;
      }
      return;
    } else if (tk == '<') {
      if (*p == '=') {
        ++p;
        tk = Le;
      } else if (*p == '<') {
        ++p;
        tk = Shl;
      } else
        tk = Lt;
      return;
    } else if (tk == '>') {
      if (*p == '=') {
        ++p;
        tk = Ge;
      } else if (*p == '>') {
        ++p;
        tk = Shr;
      } else
        tk = Gt;
      return;
    } else if (tk == '|') {
      if (*p == '|') {
        ++p;
        tk = Lor;
      } else
        tk = Or;
      return;
    } else if (tk == '&') {
      if (*p == '&') {
        ++p;
        tk = Lan;
      } else
        tk = And;
      return;
    } else if (tk == '^') {
      tk = Xor;
      return;
    } else if (tk == '%') {
      tk = Mod;
      return;
    } else if (tk == '*') {
      tk = Mul;
      return;
    } else if (tk == '[') {
      tk = Brak;
      return;
    } else if (tk == '?') {
      tk = Cond;
      return;
    } else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' || tk == '(' || tk == ')' ||
               tk == ']' || tk == ',' || tk == ':') {
      return;
    }
  }
}
