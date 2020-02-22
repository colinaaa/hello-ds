#include "Parser.hh"

#include <cstdlib>

Project::Parser::Parser() : line(1), src(0), debug(0) {
  int i;

  if ((sym = static_cast<int*>(malloc(poolSize))) == nullptr) {
    printf("could not malloc(%lld) symbol area\n", poolSize);
    exit(-1);
  }
  if ((le = e = static_cast<int*>(malloc(poolSize))) == nullptr) {
    printf("could not malloc(%lld) text area\n", poolSize);
    exit(-1);
  }
  if ((data = static_cast<char*>(malloc(poolSize))) == nullptr) {
    printf("could not malloc(%lld) data area\n", poolSize);
    exit(-1);
  }
  // init all tables to 0;
  memset(sym, 0, poolSize);
  memset(e, 0, poolSize);
  memset(data, 0, poolSize);
}
