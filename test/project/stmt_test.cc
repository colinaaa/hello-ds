#include <catch2/catch.hpp>

#include "util.hh"

TEST_CASE("stmt", "[if,while,for]") {
  REQUIRE(root.filename() == "hello-ds");
  const auto cases = {"if.c", "while.c", "for.c"};
  for (const auto& c : cases) {
    auto cmd = exec.string() + " " + (test_case_path / c).string();
    INFO("executing: " << cmd);
    auto [msg, ret_val] = exec_cmd(cmd.c_str());
    REQUIRE(ret_val == 0);
    REQUIRE(msg.empty());
  }
}
