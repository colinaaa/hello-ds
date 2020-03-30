#include <unistd.h>

#include <catch2/catch.hpp>
#include <filesystem>

#include "util.hh"

TEST_CASE("errors", "[project,error]") {
  REQUIRE(root().filename() == "hello-ds");
  const auto errors_path = test_case_path() / "errors";
  for (const auto& e : std::filesystem::directory_iterator(errors_path)) {
    auto cmd = exec().string() + " " + (errors_path / e.path()).string();
    INFO("executing: " << cmd);
    auto [msg, rtn_val] = exec_cmd(cmd.c_str());
    INFO("got error msg: " << msg);
    REQUIRE(rtn_val != 0);
    REQUIRE(!msg.empty());
  }
}
