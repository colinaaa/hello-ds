#include <unistd.h>

#include <catch2/catch.hpp>
#include <cstdlib>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "util.hh"

TEST_CASE("basic", "[basic]") {
  REQUIRE(root().filename() == "hello-ds");
  const auto cases = {"basic.c"};
  for (const auto &c : cases) {
    auto cmd = exec().string() + " " + (test_case_path() / c).string();
    INFO("executing: " << cmd);
    auto [msg, rtn_val] = exec_cmd(cmd.c_str());
    INFO("return code: " << rtn_val);
    INFO((msg.empty() ? "with empty message" : "with message: ") << msg);
    REQUIRE(msg.empty());
    REQUIRE(rtn_val == 0);
  }
}
