#include <unistd.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <tuple>

#include "util.hh"

using json = nlohmann::json;

auto parseCase(json::object_t oneCase) {
  std::string input = oneCase["input"];
  auto want = oneCase["want"];
  return std::make_tuple(input, want);
}

TEST_CASE("lex", "[project,lex]") {
  REQUIRE(root().filename() == "hello-ds");
  Project::Parser p;
  const auto cases_fs = {"lex.json"};
  for (const auto &c : cases_fs) {
    INFO("read file: " << c);
    std::ifstream cases_f(test_case_path() / c);
    json cases;
    cases_f >> cases;
    for (const auto &oneCase : cases) {
      INFO("case: " << oneCase.dump(4));
      auto [input, want] = parseCase(oneCase);
      REQUIRE(want == tokenName(p.parseToken(input)));
    }
    cases_f.close();
  }
}
