#include <fmt/printf.h>

#include "Parser.hh"

using fmt::printf;

void Project::Parser::next() {
  char *pp;

  // Get current character.
  // While current character is not `\0`.
  // The source code has been read into source code buffer and ended with `\0`.
  while ((tk = *p) != 0) {
    // Point to next character.
    ++p;
    // If current character is newline.
    if (tk == '\n') {
      if (output) {
        out << fmt::sprintf("%.*s", p - lp, lp);
      }
      if (src) {
        printf("%2d: %.*s", line, p - lp, lp);
      }
      if (output || src) {
        lp = p;
      }
      ++line;
    } else if (tk == '#') {
      // marco
      while (*p != 0 && *p != '\n') ++p;
    } else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_') {
      // indentifier
      pp = p - 1;
      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') ||
             *p == '_') {
        // compute hash value
        tk = tk * 147 + *p++;
      }
      // combine hash with length
      tk = (tk << 6) + (p - pp);

      // Point `id` to symbol table.
      id = sym;

      // While current symbol table entry is in use.
      while (id[Tk] != 0) {
        // Token exist
        if (tk == id[Hash] && (memcmp((char *)id[Name], pp, p - pp) == 0)) {
          tk = id[Tk];
          return;
        }
        // next entry
        id = id + Idsz;
      }
      // `id` is pointing to the first unused symbol table entry.
      // Store the name's string address.
      id[Name] = (int)pp;
      id[Hash] = tk;
      tk = id[Tk] = Id;
      return;
    } else if (tk >= '0' && tk <= '9') {
      // number constant
      if ((ival = tk - '0') != 0) {
        // decimal
        while (*p >= '0' && *p <= '9') ival = ival * 10 + *p++ - '0';
      } else if (*p == 'x' || *p == 'X') {
        // hex
        while ((tk = *++p) &&
               ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
          ival = (ival << 4) + (tk & 0xf) + (tk >= 'A' ? 9 : 0);
      } else {
        // octal
        while (*p >= '0' && *p <= '7') ival = ival * 8 + *p++ - '0';
      }

      // set token type
      tk = Num;
      return;
    } else if (tk == '/') {
      // comment or division
      if (*p == '/') {
        // comment
        ++p;
        while (*p != 0 && *p != '\n') ++p;
      } else {
        // division
        tk = Div;
        return;
      }
    } else if (tk == '\'' || tk == '"') {
      // Store data buffer's current location.
      pp = data;
      // While current character is not `\0` and current character is not the
      // quote character.
      while (*p != 0 && *p != tk) {
        // If current character is `\`, it is escape notation or simply `\`
        // character.
        if ((ival = *p++) == '\\') {
          // If following character is `n`, it is newline escape,
          if ((ival = *p++) == 'n') ival = '\n';
        }
        // If it is string constant, copy current character to data buffer.
        if (tk == '"') *data++ = ival;
      }
      // next char
      ++p;
      if (tk == '"')
        // If it is string constant, use the string's address as the token's
        // associated value. The token type is `"`.
        ival = reinterpret_cast<int>(pp);
      else
        // If it is character constant, use the character's value as the token's
        // associated value. Set token type be number constant.
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
