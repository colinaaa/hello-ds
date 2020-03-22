#include <docopt.h>
#include <fmt/format.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "Parser/Parser.hh"

#undef int

const std::string Version = "1.0.0";
static const char USAGE[] =
    R"(tcc
A tiny c-subset compiler frontend.

Usage:
    tcc [-hvtsg] [--indent <indent> | -i <indent>] [--output <output> | -o <output>] <file>
    tcc (-h | --help)
    tcc --version

Options:
    -v --version                     Display the verion of tcc.
    -h --help                        Display this help message.
    -t --tree                        Display the AST tree nodes.
    -i <indent> --indent=<indent>    Set the indent level of AST tree. [default: 2]
    -s --src                         Display the source file with line number.
    -g --debug                       Display debug info.
    -o <output> --output=<output>    Set the output file name. [default: out.c]
)";

auto main(int argc, char* argv[]) -> int {
  std::string filename;

  Project::Parser p{};
  int choice;
  auto args = docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "1.0.0");

  try {
    p.setTree(args["--tree"].asBool());
    p.setSrc(args["--src"].asBool());
    p.setDebug(args["--debug"].asBool());
    p.setIndent(args["--indent"].asLong());
    p.setOutput(args["--output"].asString() != "out.c");
    p.setOutputName(args["--output"].asString());
    filename = args["<file>"].asString();
  } catch (std::runtime_error& e) {
    std::cerr << e.what();
    return -1;
  }

  p.run(filename);
}
